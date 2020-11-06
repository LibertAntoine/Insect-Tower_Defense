# :ant: Insect Tower Defense

 ![InsecTower](doc/readme-img/InsecTower.png?raw=true "InsecTower")

## Table of Contents

- [**Building configuration**](#Building-configuration)
  * [**Clone repository**](#clone-repository)
  * [**Add dependencies**](#add-dependencies)
  * [**Build**](#build)
  * [**Execute**](#execute)

- [**Presentation**](#presentation)

- [**Main Features**](#main-features)

- [**Contributors**](#contributors)

- [**Dependencies**](#dependencies)


## Building configuration 
* **OS Supported :** Linux

### Clone repository 
In the local folder for the project
```bash
git clone https://github.com/LibertAntoine/Insect_Tower_Defense
```
### Add dependencies 
This project use [Cmake](https://cmake.org/) to build.
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libgl1-mesa-dev
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
```
### Build
In the project folder
```bash
mkdir build
cd build
cmake ..
make
```

### Execute
In the project folder
```bash
bin/insect_tower
```

## Presentation
<p>
Insect Tower is a tower defense game about the world of insects. The goal is to defend the Ant Queen against waves of invaders. To do this, as in reality, ants will call on other species of insects, which they will feed in exchange for their protection. Different resources can be used to increase the strength, rate of fire or range of insects.
</p>
<p>
This project is entirely developed in C, with OpenGL v2 graphics API. This is an initiative resulting from a lecture about image synthesis and algorithmics at IMAC engineering school.
</p>

Realized in May 2019.


[**More details... (FR)**](doc/Rapport_InsectTower.pdf)

<p align="center">
<img src="doc/readme-img/InsecTower2.png?raw=true" width="50%" alt="Screenshot">
<img src="doc/readme-img/InsecTower3.png?raw=true" width="50%" alt="Screenshot">
</p>


## Main Features

* OpenGL v2 rendering engine.
* Dynamic levels creation with itd or ppm file loading.
* User interface. 
* Animations and sprites management
* Shortest path algorithm.
* Dynamic trajectory management of projectiles.
* Creation of several menus.

## Contributors

* [Antoine Libert](https://github.com/LibertAntoine) - Gameplay, projectile, shortest path algorithm, monster wave.
* [Nicolas Liénart](https://github.com/nicolnt) - GUI, map, sprite, building.

## Dependencies

- [OpenGL](http://docs.gl/) - Graphic API used
- [SDL](https://wiki.libsdl.org/) - The library to create window.
- [StbImage](https://github.com/nothings/stb) - For loading images

