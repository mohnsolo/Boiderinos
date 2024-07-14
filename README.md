# Boiderinos

This is a small SFML flocking boids demo. A "boid" (short for "bird-oid") is a bird-like object with flocking behavior. Each boid starts with a random velocity but follows three fules for flocking:
1. Separation: steer away from neighbors that are too close
2. Alighnment: steer towards the average heading of neighbors
3. Cohesion: steer towards the average center of neighbors

Additionally, boids steer away from the edges of the window. This "force" is applied at some distance from the edges so that they don't go too far off the screen.

![boids](/doc/boids_screenshot.jpg)

## To Do / Ideas List
- Interaction like clicking to add boids
- Add obstacles
- Random perturbations
- Different "personalities", such as a leader or predator
- Wind?
- ~~Add some slider bars to adjust parameters on the fly (imgui)~~

## Building
Follow the [SFML Getting Started Tutorials](https://www.sfml-dev.org/tutorials/2.6/) for linking.

## Links
[Boids, by Craig Reynolds](https://www.red3d.com/cwr/boids/)