/* (c) 2024 initia labs. Licensed under BUSL-1.1 */

#ifndef __LIBCOMPILER__
#define __LIBCOMPILER__

/* Generated with cbindgen:0.26.0 */

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


enum CoverageOption {
  /**
   * Display a coverage summary for all modules in this package
   */
  CoverageOption_Summary = 0,
  /**
   * Display coverage information about the module against source code
   */
  CoverageOption_Source = 1,
  /**
   * Display coverage information about the module against disassembled bytecode
   */
  CoverageOption_Bytecode = 2,
};
typedef uint8_t CoverageOption;

enum ErrnoValue {
  ErrnoValue_Success = 0,
  ErrnoValue_Other = 1,
};
typedef int32_t ErrnoValue;

/**
 * An optional Vector type that requires explicit creation and destruction
 * and can be sent via FFI.
 * It can be created from `Option<Vec<u8>>` and be converted into `Option<Vec<u8>>`.
 *
 * This type is always created in Rust and always dropped in Rust.
 * If Go code want to create it, it must instruct Rust to do so via the
 * [`new_unmanaged_vector`] FFI export. If Go code wants to consume its data,
 * it must create a copy and instruct Rust to destroy it via the
 * [`destroy_unmanaged_vector`] FFI export.
 *
 * An UnmanagedVector is immutable.
 *
 * ## Ownership
 *
 * Ownership is the right and the obligation to destroy an `UnmanagedVector`
 * exactly once. Both Rust and Go can create an `UnmanagedVector`, which gives
 * then ownership. Sometimes it is necessary to transfer ownership.
 *
 * ### Transfer ownership from Rust to Go
 *
 * When an `UnmanagedVector` was created in Rust using [`UnmanagedVector::new`], [`UnmanagedVector::default`]
 * or [`new_unmanaged_vector`], it can be passted to Go as a return value.
 * Rust then has no chance to destroy the vector anymore, so ownership is transferred to Go.
 * In Go, the data has to be copied to a garbage collected `[]byte`. Then the vector must be destroyed
 * using [`destroy_unmanaged_vector`].
 *
 * ### Transfer ownership from Go to Rust
 *
 * When Rust code calls into Go (using the vtable methods), return data or error messages must be created
 * in Go. This is done by calling [`new_unmanaged_vector`] from Go, which copies data into a newly created
 * `UnmanagedVector`. Since Go created it, it owns it. The ownership is then passed to Rust via the
 * mutable return value pointers. On the Rust side, the vector is destroyed using [`UnmanagedVector::consume`].
 *
 */
typedef struct {
  /**
   * True if and only if this is None. If this is true, the other fields must be ignored.
   */
  bool is_none;
  uint8_t *ptr;
  size_t len;
  size_t cap;
} UnmanagedVector;

/**
 * A view into an externally owned byte slice (Go `[]byte`).
 * Use this for the current call only. A view cannot be copied for safety reasons.
 * If you need a copy, use [`ByteSliceView::to_owned`].
 *
 * Go's nil value is fully supported, such that we can differentiate between nil and an empty slice.
 */
typedef struct {
  /**
   * True if and only if the byte slice is nil in Go. If this is true, the other fields must be ignored.
   */
  bool is_nil;
  const uint8_t *ptr;
  size_t len;
} ByteSliceView;

typedef struct {
  /**
   * Compile in 'dev' mode. The 'dev-addresses' and 'dev-dependencies' fields will be used if
   * this flag is set. This flag is useful for development of packages that expose named
   * addresses that are not set to a specific value.
   */
  bool dev_mode;
  /**
   * Compile in 'test' mode. The 'dev-addresses' and 'dev-dependencies' fields will be used
   * along with any code in the 'tests' directory.
   */
  bool test_mode;
  /**
   * Generate documentation for packages
   */
  bool generate_docs;
  /**
   * Generate ABIs for packages
   */
  bool generate_abis;
  /**
   * Installation directory for compiled artifacts. Defaults to current directory.
   */
  ByteSliceView install_dir;
  /**
   * Force recompilation of all packages
   */
  bool force_recompilation;
  /**
   * Only fetch dependency repos to MOVE_HOME
   */
  bool fetch_deps_only;
  /**
   * Skip fetching latest git dependencies
   */
  bool skip_fetch_latest_git_deps;
  /**
   * bytecode version. set 0 to unset and to use default
   */
  uint32_t bytecode_version;
  /**
   * Compiler version. set 0 to unset and to use default
   */
  uint32_t compiler_version;
  /**
   * language version. set 0 to unset and to use default
   */
  uint32_t language_version;
} CompilerBuildConfig;

typedef struct {
  /**
   * Path to a package which the command should be run with respect to.
   */
  ByteSliceView package_path;
  /**
   * Print additional diagnostics if available.
   */
  bool verbose;
  /**
   * Package build options
   */
  CompilerBuildConfig build_config;
} CompilerArgument;

typedef struct {
  ByteSliceView module_name;
} CompilerCoverageBytecodeOption;

typedef struct {
  ByteSliceView module_name;
} CompilerCoverageSourceOption;

typedef struct {
  /**
   * Whether function coverage summaries should be displayed
   */
  bool functions;
  /**
   * Output CSV data of coverage
   */
  bool output_csv;
} CompilerCoverageSummaryOption;

typedef struct {
  /**
   * Whether to include private declarations and implementations into the generated
   * documentation. Defaults to false.
   */
  bool include_impl;
  /**
   * Whether to include specifications in the generated documentation. Defaults to false.
   */
  bool include_specs;
  /**
   * Whether specifications should be put side-by-side with declarations or into a separate
   * section. Defaults to false.
   */
  bool specs_inlined;
  /**
   * Whether to include a dependency diagram. Defaults to false.
   */
  bool include_dep_diagram;
  /**
   * Whether details should be put into collapsed sections. This is not supported by
   * all markdown, but the github dialect. Defaults to false.
   */
  bool collapsed_sections;
  /**
   * Package-relative path to an optional markdown template which is a used to create a
   * landing page. Placeholders in this file are substituted as follows: `> {{move-toc}}` is
   * replaced by a table of contents of all modules; `> {{move-index}}` is replaced by an index,
   * and `> {{move-include NAME_OF_MODULE_OR_SCRIP}}` is replaced by the the full
   * documentation of the named entity. (The given entity will not longer be placed in
   * its own file, so this can be used to create a single manually populated page for
   * the package.)
   */
  ByteSliceView landing_page_template;
  /**
   * Package-relative path to a file whose content is added to each generated markdown file.
   * This can contain common markdown references fpr this package (e.g. `[move-book]: <url>`).
   */
  ByteSliceView references_file;
} CompilerDocgenOption;

typedef struct {
  ByteSliceView verbosity;
  /**
   * Filters targets out from the package. Any module with a matching file name will
   * be a target, similar as with `cargo test`.
   */
  ByteSliceView filter;
  /**
   * Whether to display additional information in error reports. This may help
   * debugging but also can make verification slower.
   */
  bool trace;
  /**
   * Whether to use cvc5 as the smt solver backend. The environment variable
   * `CVC5_EXE` should point to the binary.
   */
  bool cvc5;
  /**
   * The depth until which stratified functions are expanded.
   */
  size_t stratification_depth;
  /**
   * A seed for the prover.
   */
  size_t random_seed;
  /**
   * The number of cores to use for parallel processing of verification conditions.
   */
  size_t proc_cores;
  /**
   * A (soft) timeout for the solver, per verification condition, in seconds.
   */
  size_t vc_timeout;
  /**
   * Whether to check consistency of specs by injecting impossible assertions.
   */
  bool check_inconsistency;
  /**
   * Whether to keep loops as they are and pass them on to the underlying solver.
   */
  bool keep_loops;
  /**
   * Number of iterations to unroll loops. set 0 to unset
   */
  uint64_t loop_unroll;
  /**
   * Whether output for e.g. diagnosis shall be stable/redacted so it can be used in test
   * output.
   */
  bool stable_test_output;
  /**
   * Whether to dump intermediate step results to files.
   */
  bool dump;
  /**
   * indicating that this prover run is for a test.
   */
  bool for_test;
} CompilerProveOption;

typedef struct {
  /**
   * A filter string to determine which unit tests to run. A unit test will be run only if it
   * contains this string in its fully qualified (<addr>::<module_name>::<fn_name>) name.
   */
  ByteSliceView filter;
  /**
   * Report test statistics at the end of testing
   */
  bool report_statistics;
  /**
   * Show the storage state at the end of execution of a failing test
   */
  bool report_storage_on_error;
  /**
   * Ignore compiler's warning, and continue run tests
   */
  bool ignore_compile_warnings;
  /**
   * Collect coverage information for later use with the various `package coverage` subcommands
   */
  bool compute_coverage;
} CompilerTestOption;

UnmanagedVector build_move_package(UnmanagedVector *errmsg, CompilerArgument compiler_args);

UnmanagedVector clean_move_package(UnmanagedVector *errmsg,
                                   CompilerArgument compiler_args,
                                   bool clean_cache,
                                   bool clean_byproduct,
                                   bool force);

UnmanagedVector coverage_bytecode_move_package(UnmanagedVector *errmsg,
                                               CompilerArgument compiler_args,
                                               CompilerCoverageBytecodeOption coverage_opt);

UnmanagedVector coverage_source_move_package(UnmanagedVector *errmsg,
                                             CompilerArgument compiler_args,
                                             CompilerCoverageSourceOption coverage_opt);

UnmanagedVector coverage_summary_move_package(UnmanagedVector *errmsg,
                                              CompilerArgument compiler_args,
                                              CompilerCoverageSummaryOption coverage_opt);

UnmanagedVector create_new_move_package(UnmanagedVector *errmsg,
                                        CompilerArgument compiler_args,
                                        ByteSliceView name_view);

void destroy_unmanaged_vector(UnmanagedVector v);

UnmanagedVector docgen_move_package(UnmanagedVector *errmsg,
                                    CompilerArgument compiler_args,
                                    CompilerDocgenOption docgen_opt);

UnmanagedVector new_unmanaged_vector(bool nil, const uint8_t *ptr, size_t length);

UnmanagedVector prove_move_package(UnmanagedVector *errmsg,
                                   CompilerArgument compiler_args,
                                   CompilerProveOption prove_opt);

UnmanagedVector test_move_package(UnmanagedVector *errmsg,
                                  CompilerArgument compiler_args,
                                  CompilerTestOption test_opt);

#endif /* __LIBCOMPILER__ */
