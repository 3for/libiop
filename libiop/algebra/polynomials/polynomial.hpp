/**@file
 *****************************************************************************
 Classes for polynomials.
 *****************************************************************************
 * @author     This file is part of libiop (see AUTHORS)
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/
#ifndef LIBIOP_ALGEBRA_POLYNOMIALS_POLYNOMIAL_HPP_
#define LIBIOP_ALGEBRA_POLYNOMIALS_POLYNOMIAL_HPP_

#include <cstddef>
#include <vector>

#include "libiop/algebra/exponentiation.hpp"
#include "libiop/algebra/field_subset/field_subset.hpp"
#include "libiop/algebra/field_subset/subspace.hpp"
#include "libiop/algebra/field_subset/subgroup.hpp"

namespace libiop {

template<typename FieldT>
class polynomial_base {
protected:
    std::vector<FieldT> coefficients_;
    bool coefficients_equivalent_with(const polynomial_base<FieldT> &other) const;

    void multiply_coefficients_by(const FieldT &other);
    void add_coefficients_of(const polynomial_base<FieldT> &other);

public:
    explicit polynomial_base();
    explicit polynomial_base(std::vector<FieldT> &&coefficients);

    void reserve(const std::size_t degree_bound);
    std::size_t capacity() const;
    void add_term(FieldT &&coeff);
    void remove_term(const std::size_t index);

    std::size_t num_terms() const;
    std::size_t minimal_num_terms() const;
    bool num_terms_at_most(const std::size_t bound) const;

    virtual std::size_t degree() const = 0;

    /* coefficient manipulation */
    const FieldT& operator[](const std::size_t index) const;
    FieldT& operator[](const std::size_t index);

    const std::vector<FieldT>& coefficients() const;

    virtual FieldT evaluation_at_point(const FieldT &evalpoint) const = 0;
    virtual std::vector<FieldT> evaluations_over_subspace(const affine_subspace<FieldT> &S) const = 0;

    virtual ~polynomial_base() = default;
};

template<typename FieldT>
polynomial_base<FieldT> operator+(const FieldT &lhs, const polynomial_base<FieldT> &rhs);

template<typename FieldT>
polynomial_base<FieldT> operator-(const FieldT &lhs, const polynomial_base<FieldT> &rhs);

template<typename FieldT>
class polynomial : public polynomial_base<FieldT> {
public:
    explicit polynomial();
    explicit polynomial(std::vector<FieldT> &&coefficients);

    /* if setting degree requires shrinking, truncation raises exception */
    void set_degree(const std::size_t degree_bound, const bool truncate=false);

    FieldT evaluation_at_point(const FieldT &evalpoint) const;
    std::vector<FieldT> evaluations_over_subspace(const affine_subspace<FieldT> &S) const;

    std::size_t degree() const;

    bool operator==(const polynomial<FieldT> &other) const;
    bool operator!=(const polynomial<FieldT> &other) const;
    polynomial<FieldT>& operator+=(const polynomial<FieldT> &other);
    polynomial<FieldT> operator+(const polynomial<FieldT> &other) const;

    static polynomial<FieldT> random_polynomial(const size_t degree_bound);
};

} // namespace libiop

#include "libiop/algebra/polynomials/polynomial.tcc"

#endif // LIBIOP_ALGEBRA_POLYNOMIALS_POLYNOMIAL_HPP_
