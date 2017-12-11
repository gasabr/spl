global sepia_blue
global sepia_red
global sepia_green
; rdi, rsi, rdx, rcx


align 16
c_blue_r: dd 0.272, 0.272, 0.272, 0.272
align 16
c_blue_g: dd 0.543, 0.543, 0.543, 0.543
align 16
c_blue_b: dd 0.131, 0.131, 0.131, 0.131

align 16
c_green_r: dd 0.349, 0.349, 0.349, 0.349
align 16
c_green_g: dd 0.686, 0.686, 0.686, 0.686
align 16
c_green_b: dd 0.168, 0.168, 0.168, 0.168

align 16
c_red_r: dd 0.393, 0.393, 0.393, 0.393
align 16
c_red_g: dd 0.769, 0.769, 0.769, 0.769
align 16
c_red_b: dd 0.189, 0.189, 0.189, 0.189 

align 16
max: dd 255.0, 255.0, 255.0, 255.0 ; for saturation


sepia_blue:
	movaps xmm0, [rdi] ; blue channel
	movaps xmm1, [rsi] ; green channel
	movaps xmm2, [rdx] ; red channel
	; "initialize" c matrix
	movaps xmm3, [rel c_blue_b]
	movaps xmm4, [rel c_blue_g]
	movaps xmm5, [rel c_blue_r]

	mulps xmm0, xmm3
	mulps xmm1, xmm4
	mulps xmm2, xmm5
	addps xmm0, xmm1
	addps xmm0, xmm2

	; checl owerflowing
	movaps xmm1, [rel max]
	pminsw xmm0, xmm1
	
	movaps [rcx], xmm0
	
	ret


sepia_green:
	movaps xmm0, [rdi]
	movaps xmm1, [rsi]
	movaps xmm2, [rdx]
	; "initialize" c matrix
	movaps xmm3, [rel c_green_b]
	movaps xmm4, [rel c_green_g]
	movaps xmm5, [rel c_green_r]

	mulps xmm0, xmm3
	mulps xmm1, xmm4
	mulps xmm2, xmm5
	addps xmm0, xmm1
	addps xmm0, xmm2

	; checl owerflowing
	movaps xmm1, [rel max]
	pminsw xmm0, xmm1
	
	movaps [rcx], xmm0
	
	ret


sepia_red:
	movaps xmm0, [rdi]
	movaps xmm1, [rsi]
	movaps xmm2, [rdx]
	; "initialize" c matrix
	movaps xmm3, [rel c_red_b]
	movaps xmm4, [rel c_red_g]
	movaps xmm5, [rel c_red_r]

	mulps xmm0, xmm3
	mulps xmm1, xmm4
	mulps xmm2, xmm5
	addps xmm0, xmm1
	addps xmm0, xmm2

	; checl owerflowing
	movaps xmm1, [rel max]
	pminsw xmm0, xmm1
	
	movaps [rcx], xmm0
	
	ret
