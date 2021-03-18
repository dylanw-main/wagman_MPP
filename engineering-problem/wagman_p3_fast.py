# Project 3, engineering problem, fast version
import timeit

# optimization function

def newton(f,Df,x0,epsilon,max_iter):    
    xn = x0
    for n in range(0,max_iter):
        fxn = f(xn)
        if abs(fxn) < epsilon:
            print('Found solution after',n,'iterations.')
            return xn
        Dfxn = Df(xn)
        if Dfxn == 0:
            print('Zero derivative. No solution found.')
            return None
        xn = xn - fxn/Dfxn
    print('Exceeded maximum iterations. No solution found.')
    return None

def beam():
    #Beam params: length(m), young's modulus(N/m^2), area moment of inertia(m^4) and  dist load(kN/m) w
    L=4 
    E=52000*1e3*1e4
    I=32000/(100**4)
    w=4*1e3*100

    # cantilever beam with simple support and full distributed load equations
    # deflection y and derivatives:
    y = lambda x: -w/(48*E*I)*(3*L**2*x**2-5*L*x**3+2*x**4)
    dy = lambda x: -w/(48*E*I)*(6*L**2*x-15*L*x**2+8*x**3)
    ddy = lambda x: -w/(48*E*I)*(6*L**2-30*L*x+24*x**2)

    # optimize
    maxDefx = newton(dy,ddy,L/2,1e-8,100)
    # plug in position to get deflection
    maxDefy = y(maxDefx) # Plug in position to find max deflection

    # Display max deflection
    print(f'The maximum deflection is {maxDefy*100: .5f} cm and occurs at a distance of {maxDefx: .3f} m')

#print(timeit.timeit('time.sleep(0.05)', number=100))
print(timeit.timeit('beam()', globals=globals(),number =1))