# Multi-Object Tracking using OpenCV (C++)

## 📌 Project Overview
![result](./Images/result.png)
This project implements a classical computer vision pipeline for detecting and tracking moving objects in video streams.

It uses traditional image processing methods instead of deep learning, including background subtraction, morphological filtering, contour detection, and centroid-based tracking.

---

## 🚀 Features

* Real-time video processing (camera or dataset input)
* Adaptive background modeling
* Morphological noise reduction
* Contour-based object detection
* Multi-object tracking (centroid matching)
* Bounding box visualization

---

## 🧠 Processing Pipeline

```
Input Frame
   ↓
Background Subtraction
   ↓
Foreground Mask
   ↓
Morphological Processing
   ↓
Contour Detection
   ↓
Bounding Boxes
   ↓
Centroid Tracking
   ↓
Visualization
```

---

## 🛠️ Technologies

* C++
* OpenCV
* CMake
* Linux (Ubuntu)

---

## 📂 Project Structure

```
Project3/
├── include/
├── src/
├── dataset/
├── CMakeLists.txt
├── README.md
└── .gitignore
```

---

## ▶️ How to Build & Run

```bash
mkdir build
cd build
cmake ..
make
./main
```

---

## 📈 Future Improvements

* Add trajectory visualization
* Improve tracking with Kalman Filter
* Replace classical pipeline with YOLO-based detection
* Add evaluation using ground truth dataset

---

## 👤 Author

* Martin
