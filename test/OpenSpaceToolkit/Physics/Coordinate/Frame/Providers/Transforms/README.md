# Transformation Validation Files

This folder contains reference frame transformation validation files. Their name is following the pattern:

`Frame1_Frame1_generator.csv`

And they describe the time dependent transformation that goes from `Frame1` to `Frame2`, as obtained from a 3rd party (`generator`).

Each row in the file represents a transformation in time:

- `Gregorian TAI` the date of the transformation in Gregorian calendar, TAI time scale (e.g. `1 Jan 2020 00:00:00.000`).
- `x (m),y (m),z (m)` the translation (meters).
- `vx (m/s),vy (m/s),vz (m/s)` the relative velocity (meters/s).
- `q1,q2,q3,q4` orientation quaternion.
- `wx (rad/s),wy (rad/s),wz (rad/s)` relative angular velocity (rad/s).

## STK

STK files have been generated following these steps:

1. Create a scenario (make sure it covers the time window that includes the transformation period you want to generate)
2. Right click on the scenario -> `Report & Graph Manager`
3. For each frame that you are interested in:
    - `Create new report style` and give it a name
    - Expand `Axes Choose Axes`, select the frame of interest (this will be `Frame2`), and `Insert` (blue arrow) the parameters of interest: `Time,q1,q2,q3,q4,wx,wy,wz`.
    - Adjust units for the parameters by clicking on `Units...`. Select `Gregorian TAI (TAIG)` for time and `rad/s` for relative angular velocity. You will have to do this one by one.
    - Adjust the decimal places by clickin on `Options...` and set the number of decimal digits to `12` for `q1,q2,q3,q4,wx,wy,wz`. You will have to do this one by one.
4. Once you've configured your new report style, right click on it, configure the time interval and step size that you desire for your validation file. Then right click on the report style -> `Generate Report`.
5. The previous step will have opened a `Select Axes` pop-up. Filter by `All Objects`, choose the celestial body and select the other frame (this will be `Frame1`).
6. Click `OK`, this will open the actual report, which can be exported as a CSV by clicking on `Save as .csv`.

(Steps above do not mention translation and relative velocity, which have been manually inserted as both frames share the same origin, making both of them `{0,0,0}`)

## Orekit

Orekit files have been generated using:

`frame1.getTransformTo(frame2, date)`

Where `frame1` and `frame2` are instantiated by means of the `FramesFactory`, when applicable, using:
- `IERSConventions.IERS_2010`
- `simpleEOP: false`

