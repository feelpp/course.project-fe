#include <iostream>
#include <fstream>
#include <cmath>

class Evaluator
{
public:
  virtual double operator()(double x,double y) const = 0;
private:
};

class EvaluatorExpr : public Evaluator
{
public:
  EvaluatorExpr( double(*f)(double,double) )
    :
    M_f( f )
  {}
  double operator()(double x,double y) const override { return M_f(x,y); }
private:
  double(*M_f)(double,double);
};


void test( Evaluator const& eval_f )
{
  std::cout << "test eval_f(1.2,2.2)=" << eval_f(1.2,2.2) << std::endl;
}


int main()
{
  EvaluatorExpr eval_f( [](double x,double y) { return cos(x)*sin(y); } );
  std::cout << "eval_f(1.2,2.2)=" << eval_f(1.2,2.2) << std::endl;
  test( eval_f );

  return 0;
}
