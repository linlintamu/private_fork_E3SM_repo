#include "share/io/scream_io_utils.hpp"

namespace scream {

std::string
compute_model_restart_filename (const std::string&     prefix,
                                const util::TimeStamp& timestamp)
{
  return prefix + ".r." +
         timestamp.to_string() + ".nc";
}

std::string
compute_model_output_filename (const std::string&     prefix,
                               const bool             hist_restart,
                               const OutputAvgType    avg_type,
                               const IOControl&       io_control,
                               const util::TimeStamp& timestamp,
                               const ekat::Comm*      comm,
                               const bool             filename_with_mpiranks)
{
  auto filename = prefix;
  if (hist_restart) {
    filename += ".rhist";
  }

  // Always add a time stamp
  filename += "." + e2str(avg_type);
  filename += "." + io_control.frequency_units + "_x" + std::to_string(io_control.frequency);

  // Optionally, add number of mpi ranks (useful mostly in unit tests, to run multiple MPI configs in parallel)
  if (filename_with_mpiranks) {
    EKAT_REQUIRE_MSG (comm!=nullptr,
        "Error! If filename_with_mpiranks=true, you must pass a valid comm pointer.\n");
    filename += ".np" + std::to_string(comm->size());
  }

  // Always add a time stamp
  filename += "." + timestamp.to_string();

  return filename + ".nc";
}

} // namespace scream
