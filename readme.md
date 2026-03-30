# Labs – Computer Graphics

---

## 📂 Lab 1

### 📖 Description
In this lab:
1. Rotation of a square constructed from lines around the center of the screen, repeated n times, using a specified angle
2. Translation of a square such that its center follows the circumference of a circular arc centered at the screen center
3. Drawing an airplane defined by points in its local coordinate system, scaled and translated in four directions, and rotating a separate instance around the screen center using a timer-based animation


### 🖼️ Screenshot
<div >
  <img src="images/Lab1_1.png" alt="Lab 1" width="200">
  <img src="images/lab1_2.png" alt="Lab 1" width="200">
  <img src="images/lab1_3.png" alt="Lab 1" width="200">
</div>
---

## 📂 Lab 2

### 📖 Description

Plotting of four mathematical functions— $\tan(x)$, $\sin(10x)$, $x\sin(10x)$, and $(x^2 - 2)(x + 3)$—using polyline approximation to render smooth curves. 

### 🖼️ Screenshot
<div >
  <img src="images/lab2_1.png" alt="Lab 1" width="400">

</div>

---

## 📂 Lab 3

### 📖 Description

In this lab:
1. Setting up the programmable OpenGL pipeline by implementing Vertex and Fragment shaders to transform 3D data into pixels.
2. Managing GPU memory through Vertex Buffer Objects (VBO) for data storage and Vertex Array Objects (VAO) for attribute organization.
3. Initializing windows and handling events (mouse, keyboard, display) using FreeGlut callback functions.
4. Rendering geometric primitives to create a square and a circle, including the use of Index Buffer Objects (IBO) for efficient drawing

### 🖼️ Screenshot
<div >
  <img src="images/lab3_1.png" alt="Lab 1" width="200">
<img src="images/lab3_2.png" alt="Lab 1" width="200">
<img src="images/lab3_3.png" alt="Lab 1" width="200">
</div>


## 📂 Lab 6

### 📖 Description

In this lab, the focus is on the OpenGL Visualization System, specifically handling hierarchical modeling and matrix stacks to create complex, articulated scenes. Key concepts include:

1. Matrix Stack Management: Using glPushMatrix and glPopMatrix to manage local and global coordinate systems, allowing objects to inherit transformations from their "parents."

2. Compound Transformations: Implementing the correct order of operations (Translation, Rotation, Scaling) to ensure articulated movements without breaking the object's geometry.

3. Hierarchical Robot Arm: Developing a multi-segment robotic arm where the movement of the forearm depends on the shoulder, and the fingers follow the forearm's orientation, including "shearing" movements.

4. Solar System Simulation: Modeling a dynamic system where planets orbit the sun and satellites orbit planets, using relative transformations and self-rotation logic.

### 🖼️ Screenshot
<div >
  <img src="images/lab6_1.png" alt="Lab 6" width="400">
<img src="images/lab6_2.png" alt="Lab 6" width="400">
</div>
