#include <iostream>
#include <fstream>
#include <cmath>
#include <set>

#include <Eigen/Dense>
#include <Eigen/Sparse>

int main()
{
  typedef Eigen::SparseMatrix<double,Eigen::RowMajor>  sparse_matrix_type;
  sparse_matrix_type mat(10,10);
  Eigen::VectorXd rhs(10);
  std::vector<Eigen::Triplet<double>> tripletList;

  // -----------------------------------------------------------------------//
  // assemblage de la matrice
  // -----------------------------------------------------------------------//
  for (int i=0;i<10;++i )
    {
      tripletList.push_back( Eigen::Triplet<double>(i,i, 3.0 ) );
      if ( i < 9 )
        tripletList.push_back( Eigen::Triplet<double>(i,i+1, -2.0 ) );
      if ( i > 0 )
        tripletList.push_back( Eigen::Triplet<double>(i,i-1, 5.0 ) );
      rhs(i) = 2*i;
    }
  mat.setFromTriplets(tripletList.begin(), tripletList.end());

  std::cout << "mat = " << mat << std::endl;

  // -----------------------------------------------------------------------//
  // elimination des quelques lignes de la matrices
  // -----------------------------------------------------------------------//
  std::set<int> rows = { 3,5,7 };
  for ( int rowId : rows )
    {
      for (typename sparse_matrix_type::InnerIterator it(mat,rowId); it; ++it)
        {
          if ( it.row() == it.col() )
            {
              it.valueRef() = 1.0;
            }
          else
            {
              it.valueRef() = 0;
            }
        }
    }
  std::cout << "mat = " << mat << std::endl;

  // -----------------------------------------------------------------------//
  // resolution du systeme linéaire
  // -----------------------------------------------------------------------//
  Eigen::SparseLU<sparse_matrix_type>  solver;
  solver.analyzePattern(mat); 
  solver.factorize(mat); 
  Eigen::VectorXd sol = solver.solve(rhs);

  std::cout << "sol= " << sol << std::endl;


  return 0;
}
