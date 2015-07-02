#define DEBUG_TYPE "mypass"

#include "llvm/Pass.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/Transforms/Utils/CodeExtractor.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/raw_ostream.h"

#include "clang/AST/PrettyPrinter.h"

#include<iostream>
#include <fstream>
#include <set>
#include<vector>

using namespace llvm;

STATISTIC(myPass1Counter, "my pass1");
STATISTIC(myPass2Counter, "my pass2");
STATISTIC(myPass3Counter, "my pass3");
STATISTIC(myPass4Counter, "my pass4");
STATISTIC(myPass5Counter, "my pass5");
STATISTIC(myPass6Counter, "my pass6");

namespace
{
// function pass example
struct myPass1 : public FunctionPass
{
    static char ID;
    myPass1() : FunctionPass(ID) {}

    // runOn
    virtual bool runOnFunction(Function &F)
    {
        clang::LangOptions LangOpts;
        LangOpts.CPlusPlus = true;
        clang::PrintingPolicy Policy(LangOpts);

        ++myPass1Counter;
        errs() << "my pass: (runOn) '" << F.getName() << "'\n";
        Function::arg_iterator argBegin = F.arg_begin();
        Function::arg_iterator argEnd = F.arg_end();
        int no=1;
        errs() << "Function Arguments : \n";
        for (Function::arg_iterator i = argBegin; i != argEnd; ++i)
        {
            std::string TypeS;
            llvm::raw_string_ostream s(TypeS);
//             i->printPretty(s, 0, Policy);
//             i->print(s);
            i->printAsOperand(s);
            llvm::errs() << "arg: " << s.str() << "\n";
            //errs() << "    Argument # " << no++ << " : " << *i << " , ";
        }
        errs() << "\n";
        //errs() << "Function : \n " << F << "\n";
        return false;
    }
};


// loop pass example
struct myPass2 : public BasicBlockPass
{
    static char ID;
    myPass2() : BasicBlockPass(ID) {}

    // doInit
    virtual bool doInitialization(Function &F)
    {
        errs() << "my pass2: (doInit)" << F.getName() << "\n";
        errs() << "========\n";
        return false;
    }

    // runOn
    virtual bool runOnBasicBlock(BasicBlock &BB)
    {
        ++myPass2Counter;
        errs() << "my pass2: (runOn), myParent = " << BB.getParent()->getName() << "\n";
        return false;
    }

    // doFin
    virtual bool doFinalization(Function &F)
    {
        errs() << "my pass2: (doFin)" << F.getName() << "\n";
        return false;
    }
};


struct myPass3 : public FunctionPass
{
    static char ID;
    myPass3() : FunctionPass(ID) {}

    // runOn
    virtual bool runOnFunction(Function &F)
    {
        ++myPass3Counter;
        errs() << "my pass3: (runOn) '" << F.getName() << "'\n";
        errs() << "BB in this function:\n";
        for (Function::iterator i = F.begin(), e = F.end(); i != e; ++i)
        {
            errs() << "sized " << i->size() << "\n";
            errs() << "---> " << *i << "\n";
        }
        return false;
    }
};


struct myPass4 : public BasicBlockPass
{
    static char ID;
    myPass4() : BasicBlockPass(ID) {}

    // doInit
    virtual bool doInitialization(Function &F)
    {
        errs() << "my pass4: (doInit)" << F.getName() << "\n";
        errs() << "========\n";
        return false;
    }

    // runOn
    virtual bool runOnBasicBlock(BasicBlock &BB)
    {
        ++myPass4Counter;
        errs() << "my pass4: (runOn), myParent = " << BB.getParent()->getName() << "\n";
        for (BasicBlock::iterator i = BB.begin(), e = BB.end(); i != e; ++i)
        {
            errs() << "--> " << *i << "\n";
        }
        return false;
    }

    // doFin
    virtual bool doFinalization(Function &F)
    {
        errs() << "my pass4: (doFin)" << F.getName() << "\n";
        return false;
    }
};

// function pass to print input outputs values
// used in a loop
typedef SetVector<Value *> ValueSet;
struct myPass5 : public FunctionPass
{
    static char ID;
    myPass5() : FunctionPass(ID) {}

    void getAnalysisUsage(AnalysisUsage &AU) const override
    {
        AU.setPreservesAll();
        //AU.setPreservesCFG();
        AU.addRequired<LoopInfoWrapperPass>();
        AU.addRequired<DominatorTreeWrapperPass>();
    }

    // runOn
    bool runOnFunction(Function &F) override
    {
        LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        int loopCounter=0;
        errs()<< "Function " << F.getName()+"\n";
        for( LoopInfo::iterator i=LI.begin(), e=LI.end(); i!=e; ++i)
        {
            ValueSet inputs, outputs;
            Loop* L=*i;
            loopCounter++;
            errs()<<"Loop# ";
            errs()<<loopCounter;
            errs()<<"\n";
            errs()<<*L << "\n\n";

            DominatorTree &DT = getAnalysis<DominatorTreeWrapperPass>().getDomTree();
            CodeExtractor Extractor(DT, *L);
            // Find inputs to, outputs from the code region.
            Extractor.findInputsOutputs(inputs, outputs);

//             std::vector<Type*> paramTy;
            // Add the types of the input values to the function's argument list
            errs() << "Inputs" << "\n";
            for (ValueSet::const_iterator i = inputs.begin(), e = inputs.end(); i != e; ++i)
            {
                std::string typeStr;
                llvm::raw_string_ostream COUT(typeStr);
                const Value *value = *i;
                value->printAsOperand(COUT);
//                 (value->getType())->print(COUT);
                errs() << "     value used in func: " << *value << "\n";
//                 errs() << "     type " << COUT.str() << " ";
                errs() << "     as operand " << COUT.str() << " ";
                errs() << "     name " << (value->getName()) << "\n\n";
            }
            errs() << "\n";

            // Add the types of the output values to the function's argument list
            errs() << "Outputs" << "\n";
            for (ValueSet::const_iterator i = outputs.begin(), e = outputs.end();i != e; ++i)
            {
                const Value *value = *i;
                errs() << "     value used in func: " << *value << "\n";
                errs() << "     name " << (value->getName()) << "\n";
            }
            errs() << "\n";

//             int bbCounter=0;
//             for(Loop::block_iterator bb=L->block_begin(); bb!=L->block_end(); ++bb)
//             {
//                 bbCounter+=1;
//             }
//             errs()<<": #BBs = ";
//             errs()<<bbCounter;
//             errs()<<"\n";
        }
        return (false);
    }
};

// loop pass to split loops
struct myPass6 : public LoopPass
{
    static char ID;
    myPass6() : LoopPass(ID) {}

    void getAnalysisUsage(AnalysisUsage &AU) const override
    {
        AU.setPreservesAll();
        //AU.setPreservesCFG();
        AU.addRequiredID(LoopSimplifyID);
        //AU.addRequired<LoopInfoWrapperPass>();
        AU.addRequired<DominatorTreeWrapperPass>();
        AU.addRequiredID(BreakCriticalEdgesID);
    }

    // runOn
    bool runOnLoop(Loop *L, LPPassManager &LPM) override
    {
        if (skipOptnoneFunction(L))
            return false;

        // Only visit top-level loops.
        if (L->getParentLoop())
            return false;

        // If LoopSimplify form is not available, stay out of trouble.
        if (!L->isLoopSimplifyForm())
            return false;

        DominatorTree &DT = getAnalysis<DominatorTreeWrapperPass>().getDomTree();
        bool Changed = false;

        // If there is more than one top-level loop in this function, extract all of
        // the loops. Otherwise there is exactly one top-level loop; in this case if
        // this function is more than a minimal wrapper around the loop, extract
        // the loop.
        bool ShouldExtractLoop = false;

        // Extract the loop if the entry block doesn't branch to the loop header.
        TerminatorInst *EntryTI =
        L->getHeader()->getParent()->getEntryBlock().getTerminator();
        if (!isa<BranchInst>(EntryTI) || !cast<BranchInst>(EntryTI)->isUnconditional() ||
        EntryTI->getSuccessor(0) != L->getHeader())
        {
            ShouldExtractLoop = true;
        }
        else
        {
            // Check to see if any exits from the loop are more than just return
            // blocks.
            SmallVector<BasicBlock*, 8> ExitBlocks;
            L->getExitBlocks(ExitBlocks);
            for (unsigned i = 0, e = ExitBlocks.size(); i != e; ++i)
            {
                if (!isa<ReturnInst>(ExitBlocks[i]->getTerminator()))
                {
                    ShouldExtractLoop = true;
                    break;
                }
            }
        }

        if (ShouldExtractLoop)
        {
            // We must omit landing pads. Landing pads must accompany the invoke
            // instruction. But this would result in a loop in the extracted
            // function. An infinite cycle occurs when it tries to extract that loop as
            // well.
            SmallVector<BasicBlock*, 8> ExitBlocks;
            L->getExitBlocks(ExitBlocks);
            for (unsigned i = 0, e = ExitBlocks.size(); i != e; ++i)
            {
                if (ExitBlocks[i]->isLandingPad())
                {
                    ShouldExtractLoop = false;
                    break;
                }
            }
        }

        if (ShouldExtractLoop)
        {
//             if (NumLoops == 0)
//                 return Changed;
//             --NumLoops;

            CodeExtractor Extractor(DT, *L);
            if (Extractor.extractCodeRegion() != nullptr)
            {
                errs() << "Extracted Function" << "\n";
                Changed = true;
                // After extraction, the loop is replaced by a function call, so
                // we shouldn't try to run any more loop passes on it.
                LPM.deleteLoopFromQueue(L);
            }
            ++myPass6Counter;
        }

    return Changed;
    }

};

} //end namespace

char myPass1::ID = 0;
static RegisterPass<myPass1> X1("mypass1", "my first LLVM Pass");

char myPass2::ID = 0;
static RegisterPass<myPass2> X2("mypass2", "my second LLVM Pass");

char myPass3::ID = 0;
static RegisterPass<myPass3> X3("mypass3", "my third LLVM Pass");

char myPass4::ID = 0;
static RegisterPass<myPass4> X4("mypass4", "my 4th LLVM Pass");

char myPass5::ID = 0;
static RegisterPass<myPass5> X5("mypass5", "my 5th LLVM Pass");

char myPass6::ID = 0;
static RegisterPass<myPass6> X6("mypass6", "my 6th LLVM Pass");
