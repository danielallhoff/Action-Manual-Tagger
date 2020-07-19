# Action-Manual-Tagger
This is a Qt project that makes possible to give a frame annotation level, reporting in each frame which behaviour, action and subaction is happening. As result, a behaviour analysis dataset is obtained. This information can be used to train Deep Learning or classical oriented algorithms.

## UML Diagram

![Preview](https://github.com/danielallhoff/Action-Manual-Tagger/tree/master/raw_images/uml.png?raw=true)

## Main view

![Preview](https://github.com/danielallhoff/Action-Manual-Tagger/tree/master/raw_images/interface.PNG?raw=true)

## Demo of the tool
[![Watch the video](https://img.youtube.com/vi/6sgwJqkNpR4/0.jpg)](https://youtu.be/6sgwJqkNpR4)

## Install

# Video Data Augmentation
When we are dealing with Deep learning, it is interesting to have a big amount of diverse data. If the data lacks of variability, the training process would be difficult to succeed. Data augmentation is one of the best techniques to improve data by incorporating variation. We propose an extension of the Action Manual Tagger which returns augmented data. 

![Preview](https://github.com/danielallhoff/Action-Manual-Tagger/tree/master/raw_images/data_augmentation_operations.PNG?raw=true)

For example, with this video data augmentation pipeline, one possible variation is changing image contrast to make the DL model invariant to light changes. Furthermore, the use of shifts, rotations and cropping can help the data to be more spatially varied. Applying this operations, the neural network trained with this data learns not to focus to fixed locations of an image.

The video data augmentation is an extension of applying image data augmentation over the same frames of a full video. Each operation processed over the first frame is also applied to  the rest of the video. Therefore, the typical operations over images can be used on videos as well : rotation, translation, vertical and horizontal flip, cropping, changes in brightness, add noise or blur, among others.

![Preview](https://github.com/danielallhoff/Action-Manual-Tagger/tree/master/raw_images/duplicate_frames.PNG?raw=true)


