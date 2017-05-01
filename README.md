# SolarSystem
_Simple and visual model of Solar System with VPython_

---------------

## Requirements
> - Python 2.7 (https://www.python.org/)
> - VPython (http://vpython.org/index.html)
> - wxPython (https://wxpython.org/)

No installations is required. To run the program, just:
```
python SolarSystem.py
```

## Usage

SolarSystem shows planets orbiting around the Sun considering only effects of gravity. Masses and distances are real, but radius of planets are widely exagerated, in order you can see them. It considers gravity caused by every single planet, but not other forces. Planets are considered to have no inclination with respect to the Ecliptic, and the direction of the apogeum (with respect to the Earth apogeum) is choosen randomly.

> - You can rotate image with CTRL + MOUSE and make zoom with ALT + MOUSE.
> - In the options, you can choose to see real radius of planets, to show/hide planet trails and what planets you want to be in you model.
> - **Time Speed**. Use this option for making everything to move slower/faster.
> - **Move Planets**. After clicking this button, click and drag any planet to move it to another position. Speed won't change. When you are done moving planets, click again the button (now with the name **Stop**).
> - **New Ship**. When you click this button, a spacial ship (in green) is created in the Earth surface. Click and drag in the screen to generate an arrow which is going to be the impulse communicated to the ship. You can make as many impulses as you want. When you're done, click **Stop** button.
> - **Add new planet**. Choose the mass, the radius and the virtual radius (the radius to show if _Real radius_ option in disabled) of your planet and click the button **Create a planet**. Click and drag in the screen to launch your planet; initial position will be the point you first click, and velocity will be proportional to the arrow dragged.


_This software was developed by Martin Campos for the usage in simulations for UPhysicsC in collaboration with Pere Barber Llorenç and Daniel Romero Madueño._
