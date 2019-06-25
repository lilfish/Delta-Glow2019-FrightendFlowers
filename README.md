# Glow-2019 - Frightend flowers

## Concept - the story

There was this biologist and he got bullied a lot when he was younger, the only way he found peace and comfort was by talking to his plants. The plants wouldn’t call him names or judge him.
 
But, after a while he got bored. He would share all his problems with the plants, but the plants couldn’t share theirs. He started to do experiments with the plants, with an effort to get to know the plants better.
 
After a while, he found a way to make the plants communicate with each other through light. The biologist now made visual what was going on with the plants; not only for the plants themselves but also for the eyes of the people.
 
While the biologist observed the communications, something strange happened. When the biologist was a few meters away, the plants would very calmly and rarely communicate with each other. But, when the biologist came close, the plants would go wild.
 
The biologist did not understand why and tried to figure it out. He put the plants on the floor close to his desk, and observe tirelessly until he knew what was going on.
 
After a while, he would notice something strange. When he was extremely close to a plant for a while, he noticed that that plants would suddenly stop communicating. It would take a while when they started again, and in the meantime, they wouldn’t grow. And then he knew.
 
The plants were terrified of him. Because they were afraid, they let each other know a human was near. 

The biologist was very shocked by this. So much that he decided he had to let the entire world know what was going on. This led to the creation of Frightened Flowers


## Concept - in depth

There will be multiple frames holding flower pots. Each flower pot will have a led strip to light up the flower and the pot on the outside/inside.

On top of the frame there is a motor that can lift the flower pot (with flower inside it) up and down. The motor is also able to shake the flower a bit when it's frightend.

There are also led strips sticking out of a flowerpot going to the next flower pot. These are "communication leds" and will visualize the effect of the plants talking to each other. The pots will light up or have another cool effect when a plant receives a "light pulse".

The flowers should probably also have a small vibration motor to vibrate the leaves and flower itself. This is to show the frightend effect.

## Documentation & workflow

All the documentation can be found in the git wiki found [here](https://git.fhict.nl/I393504/glow-2019/wikis/home)

As for the workflow: there are 3 main folders. These are

* Example code
* Untested
* Release
* Others

**Example code**
In this folder you are allowed to make new folders with your name. In the folder you just created you can store your example code. These example codes are codes that can run on a arduino stand-alone, but not yet in the final version.

**Untested**
When you are done with an example code and want to intergrate it with the main code, you can add this to the untested. This code should be tested on a frame before moving to the Release folder.

**Release**
When you have tested your code and it works on a frame and/or with multiple frames, you can move it to the Release. This is the code that will be uploaded to the arduinos. 

**Others**
This folder is for everything not code related. These can be presentation files, frame blueprints and the 3D case plans. For each item you can make a new folder and upload it in there. This way this project doesnt need a drive when giving it to other students.


Currently we have two arduino's per frame. Thats why you can find two folders inside the Untested and Release folder. These are called ``motorSensorController`` and ``ledstripController``. The motorSensorController is the motor & sensor arduino. The ledstripController is the code for the arduino inside the flower pot which will emit light effects and such.



