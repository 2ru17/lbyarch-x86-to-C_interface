; imgCvtGrayIntToDouble.asm
; Converts uint8_t grayscale pixels to double (0.0–1.0)
; Formula: output[i] = input[i] / 255.0

section .data
    divisor dq 255.0          ; constant 255.0 as double

section .text
bits 64
default rel
global imgCvtGrayIntToDouble

imgCvtGrayIntToDouble:
    ; rdi = input (uint8_t*)
    ; rsi = output (double*)
    ; edx = width
    ; ecx = height

    ; Calculate total pixel count: width * height
    imul    edx, ecx           ; edx = total pixel count
    movsxd  rcx, edx           ; rcx = loop counter (64-bit)

    ; Load divisor (255.0) into xmm1
    movsd   xmm1, [rel divisor]

    xor     r8, r8             ; r8 = index = 0

.loop:
    cmp     r8, rcx
    jge     .done

    ; Load single uint8_t pixel, zero-extend to 32-bit
    movzx   eax, byte [rdi + r8]

    ; Convert integer to scalar double in xmm0
    cvtsi2sd xmm0, eax         ; xmm0 = (double)pixel_value

    ; Divide by 255.0: xmm0 = xmm0 / xmm1
    divsd   xmm0, xmm1

    ; Store result as double (8 bytes per element)
    movsd   [rsi + r8*8], xmm0

    inc     r8
    jmp     .loop

.done:
    ret
