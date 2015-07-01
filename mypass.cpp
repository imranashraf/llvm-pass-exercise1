#define DEBUG_TYPE "mypass"

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/ADT/Statistic.h"
using namespace llvm;

STATISTIC(myPass1Counter, "my pass1");
STATISTIC(myPass2Counter, "my pass2");
STATISTIC(myPass3Counter, "my pass3");
STATISTIC(myPass4Counter, "my pass4");

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
        ++myPass1Counter;
        errs() << "my pass: (runOn) '" << F.getName() << "'\n";
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
        for (Function::iterator i = F.begin(), e = F.end();
                i != e; ++i)
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
}

char myPass1::ID = 0;
static RegisterPass<myPass1> X1("mypass1", "my first LLVM Pass");

char myPass2::ID = 0;
static RegisterPass<myPass2> X2("mypass2", "my second LLVM Pass");

char myPass3::ID = 0;
static RegisterPass<myPass3> X3("mypass3", "my third LLVM Pass");

char myPass4::ID = 0;
static RegisterPass<myPass4> X4("mypass4", "my 4th LLVM Pass");
