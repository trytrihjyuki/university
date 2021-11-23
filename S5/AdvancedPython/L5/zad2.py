from itertools import product

class Var():
    def __init__(self, name, const_val = None):
        self.name = name
        self.const_val = const_val

    def eval(self, valuation):
        if self.const_val is not None:
            return self.const_val
        
        return valuation[self.name]

    def __str__(self):
        if self.const_val is not None:
            return 'Const(' + str(self.const_val) + ')'
        return 'Var(' + self.name + ')'

class Operator():
    def __init__(self, name):
        if name not in ['Not', 'Or', 'And']:
           raise NotImplementedError("Not known operator!")

        self.name = name

    def __call__(self, arg1, arg2 = None):
        if self.name == 'Or':
            if arg1 is None or arg2 is None:
                raise ValueError('Binary operation, need two arguments!')
            return arg1 or arg2
        elif self.name == 'And':
            if arg1 is None or arg2 is None:
                raise ValueError('Binary operation, need two arguments!')
            return arg1 and arg2
        elif self.name == 'Not':
            if arg1 is None:
                raise ValueError('None argument!')
            return not arg1
    
    def __str__(self):
        return self.name


class Formula():
    def __init__(self, op, sub1, sub2=None):
        if op is not None and not isinstance(op, Operator):
            raise ValueError('Operator arg should be instance of Operator() class!')
        if not (isinstance(sub1, Var) or isinstance(sub1, Formula)):
            raise ValueError('Sub argument should be instance of Var() or Formula() class!')
        if (sub2 is not None) and not (isinstance(sub2, Var) or isinstance(sub2, Formula)):
            raise ValueError('Sub argument should be instance of Var() or Formula() class!')
        if (op is None) and (sub2 is not None and sub1 is not None):
            raise ValueError('No operator for two vars!')

        self.operator = op
        self.sub1 = sub1
        self.sub2 = sub2

    def eval(self, valuation):
        if self.operator is None:
            return valuation[self.sub1.name]

        if self.sub2 is None:
            return self.operator(self.sub1.eval(valuation))
        return self.operator(self.sub1.eval(valuation), self.sub2.eval(valuation))

    def __add__(self, f):
        return Formula(Operator('And'), self, f)

    def __mul__(self, f):
        return Formula(Operator('Or'), self, f)
    
    def __str__(self):
        if self.sub2 is None:
            if self.operator is None:
                return str(self.sub1)
            return str(self.operator) + '(' + str(self.sub1) + ')'
        return str(self.operator) + '(' + str(self.sub1) + ', ' + str(self.sub2) + ')'

    def tautology(self):
        def get_non_const(f, variables):
            if isinstance(f, Var): 
                if f.const_val is None:
                    variables.append(f)
                return
            if f.sub2 is not None:
                get_non_const(f.sub2, variables)
            get_non_const(f.sub1, variables)

        variables = []
        get_non_const(self, variables)
        
        for m in product([False, True], repeat=len(variables)):
            if self.eval({v.name: m[i] for (i,v) in enumerate(variables)}) == False:
                return False
        return True
    
    def simplify(self): # simplifying formula using pattern in problem statement
        if isinstance(self.sub1, Formula):
            self.sub1.simplify()
            if self.sub1.operator is None:
                self.sub1 = self.sub1.sub1
        if isinstance(self.sub2, Formula):
            self.sub2.simplify()
            if self.sub2.operator is None:
                self.sub2 = self.sub2.sub1
        if self.operator is not None:
            if self.operator.name == 'Or':
                if isinstance(self.sub1, Var) and self.sub1.const_val == False:
                    self.sub2 = self.sub1
                    self.sub2 = None
                    self.operator = None
                elif isinstance(self.sub2, Var) and self.sub2.const_val == False:
                    self.sub2 = None
                    self.operator = None
            elif self.operator.name == 'And':
                if isinstance(self.sub1, Var) and self.sub1.const_val == False:
                    self.sub2 = None
                    self.operator = None
                elif isinstance(self.sub2, Var) and self.sub2.const_val == False:
                    self.sub1 = self.sub2
                    self.sub2 = None
                    self.operator = None
            


phi = Formula(Operator('Or'), Formula(Operator('Not'), Var('x')), Formula(Operator('And'), Var('y'), Var('', True)))
psi = Formula(Operator('Or'), Var('x'), Var('',True))
ksi = Formula(Operator('And'), Formula(Operator('Or'), Var('x'), Var('', False)), Formula(Operator('And'), Var('y'), Var('', False)))
lam = Formula(None, Var('x'))

print('Str:')
print('phi: ', str(phi))
print('psi: ', str(psi))
print('ksi: ', str(ksi))
print('lam: ', str(lam))

print('\nEval:')
print('phi: ', phi.eval({'x': True, 'y': True}))
print('psi: ', psi.eval({'x': True, 'y': True}))
print('ksi: ', ksi.eval({'x': True, 'y': True}))
print('lam: ', lam.eval({'x': True, 'y': True}))

print('\nTautology:')
print('phi: ', phi.tautology())
print('psi: ', psi.tautology())
print('ksi: ', ksi.tautology())
print('lam: ', lam.tautology())

#phi.simplify()
#psi.simplify()
ksi.simplify()
#lam.simplify()
print('\nSimplify:')
print('phi: ', str(phi))
print('psi: ', str(psi))
print('ksi: ', str(ksi))
print('lam: ', str(lam))


print('\n__add__ and __mul__')
print(str(ksi) + ' + ' + str(phi) + ' = ' + str(ksi+phi))
print(str(ksi) + ' * ' + str(lam) + ' = ' + str(ksi*lam))
