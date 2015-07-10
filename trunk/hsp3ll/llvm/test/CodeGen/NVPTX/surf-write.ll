; RUN: llc < %s -march=nvptx -mcpu=sm_20 | FileCheck %s

target triple = "nvptx-unknown-nvcl"

declare void @llvm.nvvm.sust.b.1d.i32.trap(i64, i32, i32)

; CHECK: .entry foo
define void @foo(i64 %img, i32 %val, i32 %idx) {
; CHECK: sust.b.1d.b32.trap [foo_param_0, {%r{{[0-9]+}}}], {%r{{[0-9]+}}}
  tail call void @llvm.nvvm.sust.b.1d.i32.trap(i64 %img, i32 %idx, i32 %val)
  ret void
}

!nvvm.annotations = !{!1, !2}
!1 = metadata !{void (i64, i32, i32)* @foo, metadata !"kernel", i32 1}
!2 = metadata !{void (i64, i32, i32)* @foo, metadata !"wroimage", i32 0}
