# Extension: Smart Mirror

This repository contains software that you can use to make yourself a **Smart Mirror** using a Raspberry Pi or any other PC running a Linux distribution*. 

Our smart mirror has, at the point of writing this file, _four_ main widgets:

* Date & Time
* Calendar & Schedule
* Note
* Weather (newly added, not yet documented)

Each of these widgets can be toggled on or off within the code. We will continue working on ways to improve  user experience, adding more widgets and easier control to toggle and move the widgets around. But please bear in mind that we have done all of this extension in roughly two days, so of course is not perfect. 

_*although we do recommend Raspberry Pi running [Raspbian](<https://www.raspberrypi.org/downloads/raspbian/>) or a PC running Ubuntu (for a better refresh rate), as we haven't actually tested our system on other platforms, so results may vary._

## Setup Mirror:

Before actually setting up the mirror, on whichever machine you wish to use, you will need to install some dependencies.

First, this mirror uses C, OpenGL, Python3 and Google's Calendar API, so, if you do not have them installed yet, run these commands to install gcc , pip3:

```bash
$ sudo apt update
$ sudo apt install gcc
$ sudo apt install python3-pip
```

Now, run this command to install GLUT:

```bash
$ sudo apt-get install freeglut3-dev
```

And run this command to install, using pip, all the dependencies of the Google Calendar API:

```bash
$ pip install --upgrade google-api-python-client google-auth-httplib2 google-auth-oauthlib
```

Try running the same command with `pip3` instead of `pip`, in case your system doesn't use pip3 by default.



Now we can set up the actual mirror.

We will assume you are in the main project directory. If that is the case, now simply run make.

```bash
make
```

You should now have an executable called `mirror`. If you run it by typing `./mirror` inside the extension library, you should now get a black screen with white, bright text, looking similar to this image:

![mirrorss](/images/mirrorss.png)

Now you may notice that either the calendar is empty or has some redundant information for you. More details on how to setup the widgets in the next section.

To make sure it's working, just follow the clock. Its should be in sync with the clock on your PC, or the global time, if connected to the internet. The program should also be full screen. 

To close the window, just press `ALT` + `F4`.



## Widget Configuration:

### Calendar & Schedule

If you have got your mirror running, you should have a calendar that is either empty or has random data. 

That is because the mirror is connected by default to a dummy google account, for testing purposes. 

If you wish to connect your own google account to the mirror, follow these steps:

1. Turn on the Google Calendar API;

   Click this [link](https://developers.google.com/calendar/quickstart/python) and press the blue `ENABLE THE GOOGLE CALENDAR API` and download the credentials. You should now have in your downloads folder a file called `credentials.json`

2. Replace the dummy `credentials.json` with your own;

   You will find this file in the `widgets/` directory. If you are in the main folder, cd into it using this command: 

   ```bash
   cd widgets/
   ```

   Now if you run `ls`, you will see, among other files, the dummy credentials. Just replace that file with your own and you are now all set!

3. Run the mirror again, to check the changes;

   From the widgets directory, just run this command to start the mirror program:

   ```bash
   cd ../
   make
   ./mirror
   ```

   Now, the mirror should output your events. 

### Date & Time

Date & time is a fully automatic widget, so it does not need any extra configuration from the user. The user is free to change the source code to play around, yet he must beware the possibility of breaking the logic of the program.

### Note

Note is a very simple program. Given a relatively short string (note, quote, reminder), it will try to squeeze the text onto a small square and output it on the mirror. 

To change it, `cd` back into the `widgets/` directory. Then open file `quotes.txt` and change it's content to your own desire. 

Resizeable notes may come in a later update.



## General Widget Changes:

This will involve writing in the `mirror.c` file, but don't worry. If you follow the steps correctly, you shouldn't break any logic.

### Toggling

This involves commenting out the call to the function which draws the widget onto the mirror. 

Make sure you are in the main directory.

Then, open file 'mirror.c' using your editor of preference. 

Now, find a function called `void display(void)`. Underneath it, there should be a comment which says ou **MAKE CHANGES FROM HERE**.

You should now see functions named `nameWidget()`, with two parameter of type float.

To toggle a widget, just comment it or uncomment it by adding two slashes in front of the function, on the same line, similar to this:

```c
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  // MAKE CHANGES HERE
  clockWidget(100,100);
  // calendarWidget(1200,100);
  // noteWidget(100,700);
  //--------------------

  glutSwapBuffers();
}
```

In the code above, calendarWidget and noteWidget are toggled off, only clockWidget still toggled on.

After you have done your changes, save the file and run `make` and `./mirror` inside the `extension` directory to make sure everything runs properly. Now the toggled off widgets won't appear on the screen anymore.



### Changing offset

Depending on which widgets you have moved and on your taste, you may want now to reorganise the widgets. For that, you will have to change the parameters of the remaining widget function.

The offset parameters of each widget function are called offsetX and offsetY, and they represent the horizontal and vertical distance between the top left corner of the mirror and the top left corner of the widget.

If you want to change the offset, follow the steps from **Toggling**, only that you should change the parameters of the functions instead of commenting them. 

For how to adjust them, it depends a lot on the resolution of the screen you are using, so we cannot give you any advice other than by changing parameters and recompiling continuously. 

We don't have any plans for reworking on the method of changing widget offsets in the near future. 