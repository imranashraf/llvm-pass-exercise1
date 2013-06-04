#define DEBUG_TYPE "mypass"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/ADT/Statistic.h"
using namespace llvm;

STATISTIC(myPassCounter, "my pass");
STATISTIC(myPass2Counter, "my pass2");

namespace {
  // function pass example
  struct myPass : public FunctionPass {
    static char ID;
    myPass() : FunctionPass(ID) {}

    // runOn
    virtual bool runOnFunction(Function &F) {
      ++myPassCounter;
      errs() << "my pass: (runOn) '" << F.getName() << "'\n";
      return false;
    }
  };


  // loop pass example
  struct myPass2 : public BasicBlockPass {
    static char ID;
    myPass2() : BasicBlockPass(ID) {}

    // doInit
    virtual bool doInitialization(Function &F) {
      errs() << "my pass2: (doInit)" << F.getName() << "\n";
      return false;
    }

    // runOn
    virtual bool runOnBasicBlock(BasicBlock &BB) {
      ++myPass2Counter;
      errs() << "my pass2: (runOn), myParent = " << BB.getParent()->getName() << "\n";
      return false;
    }

    // doFin
    virtual bool doFinalization(Function &F) {
      errs() << "my pass2: (doFin)" << F.getName() << "\n";
      return false;
    }

  };
}

char myPass::ID = 0;
static RegisterPass<myPass> X("mypass1", "my first LLVM Pass");

char myPass2::ID = 0;
static RegisterPass<myPass2> XX("mypass2", "my second LLVM Pass");

