### Kinematic Model for a Three-Wheeled Robot with \(120^\circ\) Wheel Separation:

#### Forward Kinematics:

1. **Wheel Velocities (\(v_1, v_2, v_3\))**:

   - \(v_1 = R \cdot \omega_1\)
   - \(v_2 = R \cdot \omega_2\)
   - \(v_3 = R \cdot \omega_3\)

   Where \(R\) is the wheel radius.

2. **Robot Velocities (\(V_x, V_y\))**:

   - \(V_x = \frac{R}{2} \cdot (\sqrt{3} \cdot v_1 - \sqrt{3} \cdot v_2 + 2 \cdot v_3)\)
   - \(V_y = \frac{R}{2} \cdot (\omega_1 + \omega_2 + 2 \cdot \omega_3)\)

   Based on the \(120^\circ\) angle separation between the wheels.

3. **Total Angular Velocity (\(\omega\))**:

   - \(\omega = \frac{R}{L} \cdot (\omega_1 - \omega_2)\)

   Where \(L\) is the distance between the rear wheel and the center of the front axle.

#### Inverse Kinematics:

1. **Wheel Angular Velocities (\(\omega_1, \omega_2, \omega_3\))**:

   Given desired robot velocities (\(V_x, V_y\)) and total angular velocity (\(\omega\)), the inverse kinematic equations express the individual wheel angular velocities:

   - \(\omega_1 = \frac{2}{3R} \cdot V_x - \frac{2}{3R\sqrt{3}} \cdot V_y + \frac{2}{3L} \cdot \omega\)
   - \(\omega_2 = -\frac{1}{3R} \cdot V_x - \frac{1}{3R\sqrt{3}} \cdot V_y + \frac{2}{3L} \cdot \omega\)
   - \(\omega_3 = \frac{1}{3R} \cdot V_x + \frac{1}{3R\sqrt{3}} \cdot V_y + \frac{2}{3L} \cdot \omega\)

   These equations account for the \(120^\circ\) wheel separation and relate the desired robot motion to the required wheel angular velocities.
