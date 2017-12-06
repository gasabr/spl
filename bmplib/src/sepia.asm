global sepia_blue
global sepia_red
global sepia_green
; rdi, rsi, rdx, rcx


align 16
c_red_1: dd 0.272, 0.272, 0.272, 0.272
align 16
c_red_2: dd 0.543, 0.543, 0.543, 0.543
align 16
c_red_3: dd 0.131, 0.131, 0.131, 0.131

align 16
c_green_1: dd 0.349, 0.349, 0.349, 0.349
align 16
c_green_2: dd 0.686, 0.686, 0.686, 0.686
align 16
c_green_3: dd 0.168, 0.168, 0.168, 0.168

align 16
c_blue_1: dd 0.393, 0.393, 0.393, 0.393
align 16
c_blue_2: dd 0.769, 0.769, 0.769, 0.769
align 16
c_blue_3: dd 0.189, 0.189, 0.189, 0.189 

align 16
max: dd 255.0, 255.0, 255.0, 255.0 ; for saturation


sepia_blue:
	movq xmm0, [rdi]
	movq xmm1, [rsi]
	movq xmm2, [rdx]
	; "initialize" c matrix
	movdqa xmm3, [rel c_blue_1]
	movdqa xmm4, [rel c_blue_2]
	movdqa xmm5, [rel c_blue_3]

	mulps xmm0, xmm3
	mulps xmm1, xmm4
	mulps xmm2, xmm5
	addps xmm0, xmm1
	addps xmm0, xmm2

	; checl owerflowing
	movdqa xmm1, [rel max]
	pminsw xmm0, xmm1
	
	movdqa [rcx], xmm0
	
	ret


sepia_green:
	movq xmm0, [rdi]
	movq xmm1, [rsi]
	movq xmm2, [rdx]
	; "initialize" c matrix
	movdqa xmm3, [rel c_green_1]
	movdqa xmm4, [rel c_green_2]
	movdqa xmm5, [rel c_green_3]

	mulps xmm0, xmm3
	mulps xmm1, xmm4
	mulps xmm2, xmm5
	addps xmm0, xmm1
	addps xmm0, xmm2

	; checl owerflowing
	movdqa xmm1, [rel max]
	pminsw xmm0, xmm1
	
	movdqa [rcx], xmm0
	
	ret


sepia_red:
	movq xmm0, [rdi]
	movq xmm1, [rsi]
	movq xmm2, [rdx]
	; "initialize" c matrix
	movdqa xmm3, [rel c_red_1]
	movdqa xmm4, [rel c_red_2]
	movdqa xmm5, [rel c_red_3]

	mulps xmm0, xmm3
	mulps xmm1, xmm4
	mulps xmm2, xmm5
	addps xmm0, xmm1
	addps xmm0, xmm2

	; checl owerflowing
	movdqa xmm1, [rel max]
	pminsw xmm0, xmm1
	
	movdqa [rcx], xmm0
	
	ret
