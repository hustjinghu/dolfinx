// Copyright (C) 2012 Garth N. Wells
//
// This file is part of DOLFIN.
//
// DOLFIN is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DOLFIN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with DOLFIN. If not, see <http://www.gnu.org/licenses/>.
//
// First added:  2012-02-24
// Last changed:

#ifndef __TENSOR_LAYOUT_H
#define __TENSOR_LAYOUT_H

#include <string>
#include <utility>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "dolfin/common/types.h"
#include "GenericSparsityPattern.h"

namespace dolfin
{

  /// This class described the size and possibly the sparsity of a
  /// (sparse) tensor. It is used by the linear algebra backends to
  /// initialise tensors.

  class TensorLayout
  {

  public:

    /// Create empty tensor layout
    TensorLayout(uint primary_dim, bool sparsity_pattern);

    /// Create a tensor layout
    TensorLayout(const std::vector<uint>& dims, uint primary_dim,
                 const std::vector<std::pair<uint, uint> >& ownership_range,
                 bool sparsity_pattern);

    /// Initialize tensor layout
    void init(const std::vector<uint>& dims,
              const std::vector<std::pair<uint, uint> >& ownership_range);

    /// Return rank
    uint rank() const;

    /// Return global size for dimension i (size of tensor, includes non-zeroes)
    uint size(uint i) const;

    /// Return local range for dimension dim
    std::pair<uint, uint> local_range(uint dim) const;

    /// Return sparsity pattern (possibly null)
    boost::shared_ptr<GenericSparsityPattern> sparsity_pattern()
    { return _sparsity_pattern; }

    /// Return sparsity pattern (possibly null), const version
    const boost::shared_ptr<GenericSparsityPattern> sparsity_pattern() const
    { return _sparsity_pattern; }

    /// Return informal string representation (pretty-print)
    std::string str() const;

    // Primary storage dim (e.g., 0=row major, 1=column major)
    const uint primary_dim;

  private:

    // Shape of tensor
    std::vector<uint> shape;

    // Ownership range for each dimension
    std::vector<std::pair<uint, uint> > ownership_range;

    // Sparsity pattern
    boost::shared_ptr<GenericSparsityPattern> _sparsity_pattern;

  };

}
#endif
