# DelAbismo
A C++ game framework using SFML and OpenGL I was working on in my free time from mid-2012 to early 2013, though it had existed in several different forms since around 2010.  This iteration included a couple architectural curiosities I was interested in experimenting with, including:

* **Entity Systems** A component-entity system similar to that used in Unity3D, except more compartamentalized.  Created from a loose understanding of the [Artemis Entity System Framework](http://gamadu.com/artemis/) for Java, this system divided what you would normally call a Component in a Unity-like context into its data and behaviors.
* **Template Metaprogramming** In a misguided attempt to avoid including ```<typeinfo>```, I dabbled in some minor template debauchery to assign unique ID numbers to aforementioned Component types without explicitly labeling them with a member variable.  It was a novel way to sidestep C++'s lack of reflection, but honestly kind of unnecessary.
* **Unit Testing** Not exactly a curiosity in itself, but a bit of a stretch to fit into a game programming context.  Writing game logic for unit testing purposes forced me to implement game features in very discrete, testable chunks.  While "elegant," this approach was a huge productivity hit, especially considering this was a one-man project.

Eventually work on this petered out as I was kicking my job hunt into gear.  I've left it here for my own posterity, as a small reminder to not overengineer my own projects--a lesson I'm still having a bit of trouble with.
