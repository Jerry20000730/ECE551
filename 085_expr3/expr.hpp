#include <sstream>
#include <string.h>
#include <cstdlib>
#include <iostream>

class Expression {
public:
    virtual std::string toString() const = 0;
    virtual long evaluate() const = 0;
    virtual ~Expression() {}
};

class NumExpression : public Expression {
private:
    long num;
public:
    NumExpression(long num) : num(num) {}
    virtual std::string toString() const {
        std::stringstream res;
        res << num;
        return res.str();
    }
    virtual long evaluate() const {
      return num;
    }
    virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
private:
  Expression * lhs;
  Expression * rhs;

public:
  PlusExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return result.str();
  }
  virtual long evaluate() const {
    return lhs->evaluate() + rhs->evaluate();
  }
  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

class MinusExpression : public Expression {
private:
  Expression * lhs;
  Expression * rhs;
public:
  MinusExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return result.str();
  }
  virtual long evaluate() const {
    return lhs->evaluate() - rhs->evaluate();
  }
  ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression {
private:
  Expression * lhs;
  Expression * rhs;
public:
  TimesExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return result.str();
  }
  virtual long evaluate() const {
    return lhs->evaluate() * rhs->evaluate();
  }
  ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};

class DivExpression : public Expression {
private:
  Expression * lhs;
  Expression * rhs;
public:
  DivExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }
  std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return result.str();
  }
  virtual long evaluate() const {
    return lhs->evaluate() / rhs->evaluate();
  }
  ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};