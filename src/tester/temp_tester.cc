#include <string>
#include <bitset>
#include <iostream>
#include <memory>

#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/CodeGen/BackendUtil.h>
#include <llvm/Support/VirtualFileSystem.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>

#include "util.hh"

using namespace std;
using namespace clang;
using namespace llvm;

int main( int argc, char * argv[] ) 
{
  cout << argc << endl;

  string file_content = util::read_file( argv[1] ); 

  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmPrinters();
  llvm::InitializeAllAsmParsers();

  // Create compiler instance
  clang::CompilerInstance compilerInstance;
  auto& compilerInvocation = compilerInstance.getInvocation();
 
  // Create diagnostic engine
  auto& diagOpt = compilerInvocation.getDiagnosticOpts();
  diagOpt.DiagnosticLogFile = "-";

  string diagOutput;
  raw_string_ostream diagOS ( diagOutput );
  auto diagPrinter = make_unique<TextDiagnosticPrinter>( diagOS, new DiagnosticOptions() );

  IntrusiveRefCntPtr<DiagnosticsEngine> diagEngine = compilerInstance.createDiagnostics( &diagOpt, diagPrinter.get(), false );

  // Create File System
  IntrusiveRefCntPtr<vfs::OverlayFileSystem> RealFS( new vfs::OverlayFileSystem( vfs::getRealFileSystem() ) );
  IntrusiveRefCntPtr<vfs::InMemoryFileSystem> InMemFS( new vfs::InMemoryFileSystem() );
  RealFS->pushOverlay( InMemFS );

  InMemFS->addFile( "./add-new.c", 0, MemoryBuffer::getMemBuffer( file_content ) );
  // InMemFS->addFile( "./" + wasm_name + ".h", 0, MemoryBuffer::getMemBuffer( h_content ) );
  // InMemFS->addFile( "./wasm_rt.h", 0, MemoryBuffer::getMemBuffer( wasm_rt_content ) );

  compilerInstance.setFileManager( new FileManager( FileSystemOptions{}, RealFS ) );
  
  // auto diskFile = RealFS->openFileForRead( "/usr/include/string.h" );
  // cout << ( string )( ( *( *diskFile )->getBuffer( "ignore" ) )->getBuffer() ) << endl;

  // Create arguments
  const char *Args[] = { "add-new.c" , "-I/usr/include", "-I/usr/include/x86_64-linux-gnu", "-I/usr/lib/llvm-10/lib/clang/10.0.0/include" };
  CompilerInvocation::CreateFromArgs( compilerInvocation, Args, *diagEngine );
   
  cout << diagOS.str() << endl; 
  cout << sys::getDefaultTargetTriple() << endl;
  auto &headerSearchOpts = compilerInvocation.getHeaderSearchOpts();
  cout << "Sysroot: " << headerSearchOpts.Sysroot << endl;
  for (const auto& entry : headerSearchOpts.UserEntries)
  {
    cout << "Entry path: " << entry.Path << " group: " << entry.Group << endl;
  }
  for (const auto& entry : headerSearchOpts.SystemHeaderPrefixes)
  {
    cout << "Header prefix: " << entry.Prefix << endl;
  }

  LLVMContext context;
  CodeGenAction *action = new EmitLLVMOnlyAction( &context );
  auto &targetOptions = compilerInstance.getTargetOpts();
  targetOptions.Triple = llvm::sys::getDefaultTargetTriple();
  compilerInstance.createDiagnostics( diagPrinter.get(), false );
  
  if ( !compilerInstance.ExecuteAction( *action ) )
  {
    cout << "Failed to execute action." << endl;
  cout << diagOS.str() << endl; 
  }

  unique_ptr<llvm::Module> module = action->takeModule() ;
  if ( !module )
  {
    cout << "Failed to take module." << endl;
  cout << diagOS.str() << endl; 
  }

  // set up llvm target machine
  auto &CodeGenOpts = compilerInstance.getCodeGenOpts();
  auto &Diagnostics = compilerInstance.getDiagnostics();

  if ( module->getTargetTriple() != targetOptions.Triple ) 
  {
    cout << "Wrong target triple" << endl;
    module->setTargetTriple( targetOptions.Triple );
  }

  std::string res;
  raw_string_ostream Str_OS ( res );
  auto OS = make_unique<buffer_ostream>( Str_OS );

  EmitBackendOutput(Diagnostics, compilerInstance.getHeaderSearchOpts(), CodeGenOpts,
                    targetOptions, compilerInstance.getLangOpts(),
                    compilerInstance.getTarget().getDataLayout(), module.get(), Backend_EmitObj,
                    std::move( OS ));
  

  return 0;
}
