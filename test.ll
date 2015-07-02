; ModuleID = 'test.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.Book = type { i32, [10 x i8] }

@.str = private unnamed_addr constant [8 x i8] c"aFunc()\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.2 = private unnamed_addr constant [15 x i8] c"enter myfunc()\00", align 1
@.str.3 = private unnamed_addr constant [14 x i8] c"QQ XD Orz %d\0A\00", align 1
@.str.4 = private unnamed_addr constant [9 x i8] c" sum %d\0A\00", align 1
@.str.5 = private unnamed_addr constant [15 x i8] c"leave myfunc()\00", align 1
@.str.6 = private unnamed_addr constant [8 x i8] c"in main\00", align 1
@.str.7 = private unnamed_addr constant [15 x i8] c"after myfunc()\00", align 1

; Function Attrs: nounwind uwtable
define i32 @aFunc(i32 %par) #0 {
entry:
  %par.addr = alloca i32, align 4
  %sum = alloca i32, align 4
  %books = alloca [25 x %struct.Book], align 16
  %i = alloca i32, align 4
  %fact = alloca i32, align 4
  store i32 %par, i32* %par.addr, align 4
  store i32 0, i32* %sum, align 4
  %call = call i32 @puts(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0))
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %0, 10
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %1 = load i32, i32* %par.addr, align 4
  %mul = mul nsw i32 %1, 2
  store i32 %mul, i32* %fact, align 4
  %2 = load i32, i32* %sum, align 4
  %3 = load i32, i32* %i, align 4
  %add = add nsw i32 %2, %3
  %4 = load i32, i32* %fact, align 4
  %add1 = add nsw i32 %add, %4
  store i32 %add1, i32* %sum, align 4
  %5 = load i32, i32* %i, align 4
  %6 = load i32, i32* %i, align 4
  %idxprom = sext i32 %6 to i64
  %arrayidx = getelementptr inbounds [25 x %struct.Book], [25 x %struct.Book]* %books, i32 0, i64 %idxprom
  %pages = getelementptr inbounds %struct.Book, %struct.Book* %arrayidx, i32 0, i32 0
  store i32 %5, i32* %pages, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %7 = load i32, i32* %i, align 4
  %inc = add nsw i32 %7, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %8 = load i32, i32* %sum, align 4
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i32 %8)
  %9 = load i32, i32* %sum, align 4
  ret i32 %9
}

declare i32 @puts(i8*) #1

declare i32 @printf(i8*, ...) #1

; Function Attrs: nounwind uwtable
define void @myfun() #0 {
entry:
  %sum = alloca i32, align 4
  %Arr = alloca i32*, align 8
  %i = alloca i32, align 4
  %i4 = alloca i32, align 4
  %fact = alloca i16, align 2
  %j = alloca i32, align 4
  store i32 0, i32* %sum, align 4
  %call = call noalias i8* @malloc(i64 400) #3
  %0 = bitcast i8* %call to i32*
  store i32* %0, i32** %Arr, align 8
  %call1 = call i32 @puts(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i32 0, i32 0))
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %1, 10
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %i, align 4
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.3, i32 0, i32 0), i32 %2)
  %3 = load i32, i32* %i, align 4
  %call3 = call i32 @aFunc(i32 %3)
  store i32 %call3, i32* %sum, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %4 = load i32, i32* %i, align 4
  %inc = add nsw i32 %4, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %i4, align 4
  br label %for.cond.5

for.cond.5:                                       ; preds = %for.inc.14, %for.end
  %5 = load i32, i32* %i4, align 4
  %cmp6 = icmp slt i32 %5, 10
  br i1 %cmp6, label %for.body.7, label %for.end.16

for.body.7:                                       ; preds = %for.cond.5
  store i16 2, i16* %fact, align 2
  store i32 0, i32* %j, align 4
  br label %for.cond.8

for.cond.8:                                       ; preds = %for.inc.11, %for.body.7
  %6 = load i32, i32* %j, align 4
  %cmp9 = icmp slt i32 %6, 10
  br i1 %cmp9, label %for.body.10, label %for.end.13

for.body.10:                                      ; preds = %for.cond.8
  %7 = load i32, i32* %i4, align 4
  %8 = load i16, i16* %fact, align 2
  %conv = sext i16 %8 to i32
  %mul = mul nsw i32 %7, %conv
  %9 = load i32, i32* %i4, align 4
  %idxprom = sext i32 %9 to i64
  %10 = load i32*, i32** %Arr, align 8
  %arrayidx = getelementptr inbounds i32, i32* %10, i64 %idxprom
  store i32 %mul, i32* %arrayidx, align 4
  br label %for.inc.11

for.inc.11:                                       ; preds = %for.body.10
  %11 = load i32, i32* %j, align 4
  %inc12 = add nsw i32 %11, 1
  store i32 %inc12, i32* %j, align 4
  br label %for.cond.8

for.end.13:                                       ; preds = %for.cond.8
  br label %for.inc.14

for.inc.14:                                       ; preds = %for.end.13
  %12 = load i32, i32* %i4, align 4
  %inc15 = add nsw i32 %12, 1
  store i32 %inc15, i32* %i4, align 4
  br label %for.cond.5

for.end.16:                                       ; preds = %for.cond.5
  %13 = load i32, i32* %sum, align 4
  %call17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.4, i32 0, i32 0), i32 %13)
  %call18 = call i32 @puts(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.5, i32 0, i32 0))
  ret void
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval
  %call = call i32 @puts(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.6, i32 0, i32 0))
  call void @myfun()
  %call1 = call i32 @puts(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.7, i32 0, i32 0))
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.7.0 (trunk 240624)"}
