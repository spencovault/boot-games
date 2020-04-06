; Based on the boot script found here:
; https://stackoverflow.com/questions/27669275/undefined-reference-to-in-os-kernel-linking

; These symbols are defined by the linker. We use them to zero BSS section
extern __bss_start
extern __bss_sizew

; These symbols are length (in sectors) of the kernel,
; and segment in memory to start reading to
extern __disk_load_num_sectors
extern __disk_load_seg

extern __sector_sizew;

; Mmory address to relocate the bootsector from / to
extern __boot_base_addr
extern __boot_reloc_addr

; This is the C entry point defined in kmain.c
extern kernelmain               ; kernelmain is C entry point
global boot_start               ; Make this global to suppress linker warning

KERNEL_LBA_START equ 1          ; Logical Block Address(LBA) kernel starts on
                                ;     LBA 1 = sector after boot sector
KERNEL_LBA_END   equ KERNEL_LBA_START + __disk_load_num_sectors
                                ; Logical Block Address(LBA) kernel ends at
DISK_RETRIES     equ 3          ; Number of times to retry on disk error

section .text
bits 16

; Include a BPB (1.44MB floppy with FAT12)
%include "bpb.inc"

boot_start:
    ; This code up until label .reloc must be position independent
    xor eax, eax                ; DS=0 since we use ORG 0x7c00. 0x0000<<4+0x7c00=0x7c00
    mov ds, ax
    mov es, ax
    mov ss, ax                  ; Stack at 0x0000:0x0000
    mov esp, eax                ; After first push will be 0x0000:0xfffe at top of 64kb

    ; Copy bootloader from  __boot_base_addr (0x7c00) to __boot_reloc_addr (0x600)
    ; We copy the bootloader to low memory above the BIOS Data Area (BDA) to allow
    ; more space for the kernel.
    cld
    mov cx, __sector_sizew
    mov si, __boot_base_addr
    mov di, __boot_reloc_addr
    rep movsw

    ; Jump to the relocated boot sector and set CS=0
    jmp 0x0000:.reloc
.reloc:

    ; Read kernel 1 sector at a time until kernel loaded
load_kernel:
    mov [bootDevice], dl        ; Save boot drive
    mov di, __disk_load_seg     ; DI = Current segment to read into
    mov si, KERNEL_LBA_START    ; SI = LBA that kernel starts at
    jmp .chk_for_last_lba       ; Check to see if we are last sector in kernel

.read_sector_loop:
    mov bp, DISK_RETRIES        ; Set disk retry count

    call lba_to_chs             ; Convert current LBA to CHS
    mov es, di                  ; Set ES to current segment number to read into
    xor bx, bx                  ; Offset zero in segment

.retry:
    mov ax, 0x0201              ; Call function 0x02 of int 13h (read sectors)
                                ;     AL = 1 = Sectors to read
    int 0x13                    ; BIOS Disk interrupt call
    jc .disk_error              ; If CF set then disk error

.success:
    add di, 512>>4              ; Advance to next 512 byte segment (0x20*16=512)
    inc si                      ; Next LBA

.chk_for_last_lba:
    cmp si, KERNEL_LBA_END      ; Have we reached the last kernel sector?
    jl .read_sector_loop        ;     If we haven't then read next sector

.kernel_loaded:
    jmp launch_kernel           ; Do realmode initialization and run kernel

.disk_error:
    xor ah, ah                  ; Int13h/AH=0 is drive reset
    int 0x13
    dec bp                      ; Decrease retry count
    jge .retry                  ; If retry count not exceeded then try again

error_end:
    ; Unrecoverable error; print drive error; enter infinite loop
    mov si, diskErrorMsg        ; Display disk error message
    call print_string
    cli
.error_loop:
    hlt
    jmp .error_loop

; Function: print_string
;           Display a string to the console on display page 0
;
; Inputs:   SI = Offset of address to print
; Clobbers: AX, BX, SI

print_string:
    mov ah, 0x0e                ; BIOS tty Print
    xor bx, bx                  ; Set display page to 0 (BL)
    jmp .getch
.repeat:
    int 0x10                    ; print character
.getch:
    lodsb                       ; Get character from string
    test al,al                  ; Have we reached end of string?
    jnz .repeat                 ;     if not process next character
.end:
    ret

;    Function: lba_to_chs
; Description: Translate Logical block address to CHS (Cylinder, Head, Sector).
;              Works for all valid FAT12 compatible disk geometries.
;
;   Resources: http://www.ctyme.com/intr/rb-0607.htm
;              https://en.wikipedia.org/wiki/Logical_block_addressing#CHS_conversion
;              https://stackoverflow.com/q/45434899/3857942
;              Sector    = (LBA mod SPT) + 1
;              Head      = (LBA / SPT) mod HEADS
;              Cylinder  = (LBA / SPT) / HEADS
;
;      Inputs: SI = LBA
;     Outputs: DL = Boot Drive Number
;              DH = Head
;              CH = Cylinder (lower 8 bits of 10-bit cylinder)
;              CL = Sector/Cylinder
;                   Upper 2 bits of 10-bit Cylinders in upper 2 bits of CL
;                   Sector in lower 6 bits of CL
;
;       Notes: Output registers match expectation of Int 13h/AH=2 inputs
;
lba_to_chs:
    push ax                     ; Preserve AX
    mov ax, si                  ; Copy LBA to AX
    xor dx, dx                  ; Upper 16-bit of 32-bit value set to 0 for DIV
    div word [sectorsPerTrack]  ; 32-bit by 16-bit DIV : LBA / SPT
    mov cl, dl                  ; CL = S = LBA mod SPT
    inc cl                      ; CL = S = (LBA mod SPT) + 1
    xor dx, dx                  ; Upper 16-bit of 32-bit value set to 0 for DIV
    div word [numHeads]         ; 32-bit by 16-bit DIV : (LBA / SPT) / HEADS
    mov dh, dl                  ; DH = H = (LBA / SPT) mod HEADS
    mov dl, [bootDevice]        ; boot device, not necessary to set but convenient
    mov ch, al                  ; CH = C(lower 8 bits) = (LBA / SPT) / HEADS
    shl ah, 6                   ; Store upper 2 bits of 10-bit Cylinder into
    or  cl, ah                  ;     upper 2 bits of Sector (CL)
    pop ax                      ; Restore scratch registers
    ret

; Set up segments so they are 0, zero out the BSS memory and transfer
; control to the function kernelmain
launch_kernel:
    xor ax, ax
    mov es, ax
    mov fs, ax
    mov gs, ax                  ; ES=FS=GS=0 (we set DS=SS=0 previously)

    ; We need to zero out the BSS section. We'll do it a WORD at a time
    mov edi, __bss_start        ; Start address of BSS
    mov ecx, __bss_sizew        ; Length of BSS in WORDS
                                ; Clear memory with value in AX (0x0000)
    rep stosw                   ; Do clear using string store instruction
                                ;     Clear 2 bytes at a time
    call dword kernelmain       ; Call kernel's "C" main entry point

.end_loop:                      ; Loop forever to terminate when kernel main is finished
    hlt
    jmp .end_loop


section .data
; Uncomment these lines if not using a BPB (via bpb.inc)
; numHeads:        dw 2         ; 1.44MB Floppy has 2 heads & 18 sector per track
; sectorsPerTrack: dw 18

bootDevice:      db 0x00
diskErrorMsg:    db "Unrecoverable disk error!", 0