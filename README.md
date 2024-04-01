# Multiple Scattering in Charged Particle Tracking

When charged particles move through a medium, the Coulomb interactions between the charge of the incoming particle and the Coulomb field of the medium's nucleus will alter the trajectory and energy of the incoming particle.

## Common Models for Multiple Scattering

Commonly used models to describe multiple scattering include the Molière model, Gaussian model, and the Landau-Pomeranchuk-Migdal model.

One of the most widely used models is the Molière model. Molière assumes that after each interaction, the new direction of the particle is randomly chosen according to a Gaussian distribution:

$\theta _0 = \theta^{rms} _{space} = \frac{1}{\sqrt{2}} \theta^{rms} _{space}$

The scattering angle distribution can be described by a Gaussian function with zero mean and standard deviation determined by the magnitude of the scattering angle:

$P(\theta) = \frac{1}{\sqrt{2\pi} \theta_{rms}} e^{-\frac{\theta^2}{2\theta_{rms}^2}}$

Here, $\theta$ is the scattering angle, and $\theta_{rms}$ is the root mean square scattering angle according to the Molière model.

## Molière Model

The scattering angle is calculated using a Gaussian from the Molière model:

$\theta _0 = \frac{13.6 \text{ MeV}}{\beta c p} z \sqrt{\frac{x}{X_0}} \left[1 + 0.0038 \ln\left(\frac{x}{X_0}\right)\right]$

Where:
- $\beta c$ is the velocity of the incoming particle.
- $p$ is the momentum of the incoming particle.
- $z$ is the charge of the incoming particle.
- $\frac{x}{X_0}$ is the ratio of the radiation length of the scattering medium over the length of radiation.

The radiation length $X_0$ can be approximated as: $X_0 \approx \frac{716.4 A}{Z(Z+1) \ln\left(\frac{287}{\sqrt{Z}}\right)}$

This $\theta_0$ value suits the Molière distribution for charged particles with velocities close to the speed of light ($\beta \approx 1$) for all $z$.

## Angular Distribution in Space and Plane

The angular distribution in space and the plane is approximated as:

$\frac{1}{2\pi \theta_0^2} e^{-\frac{\theta_{space}^2}{2\theta_0^2}}d\Omega$
$\frac{1}{\sqrt{2\pi} \theta_0} e^{-\frac{\theta^2_{plane}}{2\theta_0^2}} d\theta_{plane}$

Where:
- $\theta_{space}^2 \approx (\theta_{plane, x}^2 + \theta_{plane, y}^2)$ with $x$ and $y$ being orthogonal to the motion.
- $d\Omega \approx d\theta_{plane, x}~d\theta_{plane, y}$

However, in reality, for small scattering angles, the angular distribution can approximate a Gaussian distribution, but for larger scattering angles, it will have a longer tail compared to a Gaussian distribution.
