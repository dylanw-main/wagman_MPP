**Project 3**
Dylan Wagman
MPP engineering problem project
Contains:
- slower version (using scipy optimization)
- faster version (using my own newton fn) **81% faster on pi**
- problem image
- feedback file

**Pi zero execution time for slower:**


    pi@raspberrypi:~ $ python3 wagman_p3_slower.py
    The maximum deflection is -0.33330 cm and occurs at a distance of  2.314 m
    exec time: 0.016572079000070516


**Mac execution time for slower:**


    The maximum deflection is -0.33330 cm and occurs at a distance of  2.314 m
    exec time: 0.00023808800000002517


**Pi zero execution time for faster:**


    pi@raspberrypi:~ $ python3 wagman_p3_fast.py
    Found solution after 3 iterations.
    The maximum deflection is -0.33330 cm and occurs at a distance of  2.314 m
    exec time: 0.0030260149997047847


**Mac execution time for faster:**


    Found solution after 3 iterations.
    The maximum deflection is -0.33330 cm and occurs at a distance of  2.314 m
    exec time: 7.072899999999854e-05
