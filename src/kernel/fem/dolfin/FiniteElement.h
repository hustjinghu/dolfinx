// Copyright (C) 2002 Johan Hoffman and Anders Logg.
// Licensed under the GNU GPL Version 2.

// Definition of a finite element. This is a modified version
// or the standard definition given by Ciarlet (1976).
//                       
//   1.   A reference cell K0
//
//   2.a) A function space P on the reference cell (the local trial space)
//     b) A map I from local to global degrees of freedom
//
//   3.a) A function space Q on the reference cell (the local test space)
//     b) A map J from local to global degrees of freedom

#ifndef __FINITE_ELEMENT_H
#define __FINITE_ELEMENT_H

#include <dolfin/constants.h>
#include <dolfin/FunctionSpace.h>
#include <dolfin/ShapeFunction.h>
#include <dolfin/shapefunctions.h>

namespace dolfin {

  class ExpressionFunction;

  class FiniteElement {
  public:

    // Constructor
    FiniteElement(FunctionSpace& trial, FunctionSpace& test) : P(&trial), Q(&test) {};
    
    // Dimension (of trial space)
    int dim() const;
    
    // Update function spaces
    void update(const Map* map);
    
    
    // Iterator over shape functions in the local trial space
    class TrialFunctionIterator {
    public:
      
      TrialFunctionIterator(const FiniteElement& element);
      TrialFunctionIterator(const FiniteElement* element);
      
      // Global dof (map I)
      int dof(const Cell& cell) const;
      
      // Evaluation of dof
      real dof(const Cell& cell, const ExpressionFunction& f, real t) const;
      
      int  index() const;
      bool end() const;
      void operator++();
      operator FunctionSpace::ShapeFunction() const;
      FunctionSpace::ShapeFunction& operator*() const;
      FunctionSpace::ShapeFunction* operator->() const;
      
    private:
      
      const FiniteElement* e;
      FunctionSpace::Iterator v;
      
    };
    
    // Iterator over shape functions in the local test space
    class TestFunctionIterator {
    public:
      
      TestFunctionIterator(const FiniteElement& element);
      TestFunctionIterator(const FiniteElement* element);
      
      // Global dof (map J)
      int dof(const Cell& cell) const;
      
      // Evaluation of dof
      real dof(const Cell& cell, const ExpressionFunction& f, real t) const;
      
      int  index() const;                               // Index in list
      bool end() const;                                 // End of list?
      void operator++();                                // Increment
      operator FunctionSpace::ShapeFunction() const;    // Cast to ShapeFunction
      FunctionSpace::ShapeFunction& operator*() const;  // Dereferencing
      FunctionSpace::ShapeFunction* operator->() const; // -> access
      
    private:
      
      const FiniteElement* e;
      FunctionSpace::Iterator v;
      
    };

    
    // Vector finite element
    class Vector {
    public:
      
      Vector(int size);
      //Vector(const Vector& v);
      //Vector(const FiniteElement& v0, const FiniteElement& v1, const FiniteElement& v2);
      ~Vector();
      
      int size() const;
      
      FiniteElement*& operator() (int i);
      
      // Iterator over shape functions in the local trial space
      class TrialFunctionIterator {
      public:
	
	TrialFunctionIterator(FiniteElement::Vector& element);
	TrialFunctionIterator(FiniteElement::Vector* element);
	
	// Global dof (mapping I)
	int dof(const Cell& cell) const;
	
	// Evaluation of dof
	//real dof(const Cell& cell, const ExpressionFunction& f, real t) const;
	//int  index() const;
	bool end() const;
	void operator++();
	//operator FunctionSpace::ShapeFunction() const;
	FunctionSpace::ShapeFunction::Vector& operator*();
	FunctionSpace::ShapeFunction::Vector* operator->();
      
      private:
	
	FiniteElement::Vector& e;
	FiniteElement::TrialFunctionIterator uiter;
	int componentiter;

	FunctionSpace::ShapeFunction::Vector shapefunction;
	//FunctionSpace::ShapeFunction zero;
      };
      



      // Iterator over shape functions in the local test space
      class TestFunctionIterator {
      public:
	
	TestFunctionIterator(FiniteElement::Vector& element);
	TestFunctionIterator(FiniteElement::Vector* element);
	
	// Global dof (mapping I)
	int dof(const Cell& cell) const;
	
	// Evaluation of dof
	//real dof(const Cell& cell, const ExpressionFunction& f, real t) const;
	//int  index() const;
	bool end() const;
	void operator++();
	//operator FunctionSpace::ShapeFunction() const;
	FunctionSpace::ShapeFunction::Vector& operator*();
	FunctionSpace::ShapeFunction::Vector* operator->();
      
      private:
	
	FiniteElement::Vector& e;
	FiniteElement::TestFunctionIterator viter;
	int componentiter;

	FunctionSpace::ShapeFunction::Vector shapefunction;
	//FunctionSpace::ShapeFunction zero;
      };
      
    private:
      FiniteElement** v;
      int _size;
    };


    // Friends
    friend class TrialFunctionIterator;
    friend class TestFunctionIterator;
    friend class Vector::TrialFunctionIterator;
    friend class Vector::TestFunctionIterator;
    
  private:
    
    FunctionSpace* P; // Local trial space on reference cell
    FunctionSpace* Q; // Local test space on reference cell

    FunctionSpace::ShapeFunction zero;
    
  };
  
}

#endif
