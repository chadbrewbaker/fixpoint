#include <memory>
#include <string>
#include <vector>

#include "parser.hh"
#include "spans.hh"

/**
 * Structure of program files:
 * --------------------------------
 *  header:number of input entries
 *         number of output entries
 * --------------------------------
 *        Input entries
 * --------------------------------
 *        Output entries
 * --------------------------------
 *        Wasm module
 * --------------------------------
 */

class Program {
  private:
    // Name of the program
    std::string name_;
    
    // List of named input symbols
    std::vector<std::string> inputs_;
    // List of named output symbols
    std::vector<std::string> outputs_;

    // Code and data section of the program
    std::shared_ptr<const char> code_;
    // Entry point of init function
    uint64_t init_entry_;
    // Entry point of main function
    uint64_t main_entry_;
    // Location of memory variable;
    uint64_t mem_loc_;

  public:
    Program( std::string name, std::vector<std::string> && inputs, std::vector<std::string> && outputs,
             std::shared_ptr<const char> code, uint64_t init_entry, uint64_t main_entry, uint64_t mem_loc ) 
      : name_( name ),
        inputs_( std::move( inputs ) ),
        outputs_( std::move( outputs ) ),
        code_( code ),
        init_entry_( init_entry ),
        main_entry_( main_entry ),
        mem_loc_( mem_loc )
    {}
};
