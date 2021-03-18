# Project 3, engineering problem, slower version
import timeit
from scipy.optimize import fsolve

# optimization function
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
    
    # optimize
    maxDefx = fsolve(dy, L/2)[0]
    
    # plug in position to get deflection
    maxDefy = y(maxDefx) # Plug in position to find max deflection

    # Display max deflection
    print(f'The maximum deflection is {maxDefy*100: .5f} cm and occurs at a distance of {maxDefx: .3f} m')


print(timeit.timeit('beam()', globals=globals(),number =1))