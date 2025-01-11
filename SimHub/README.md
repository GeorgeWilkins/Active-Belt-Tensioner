# SimHub Files
There are two files in this directory:
- [Device.js](Device.js): The raw JS code that you can tweak to customise your tensioner's behaviour. It's included as reference, but not needed if you import the file below instead
- [Device.shsds](Device.shsds): An importable SimHub-specific file that automatically configures the 'Custom Serial Device' for you, including the JS code above and the various settings sliders that control torque settings

After importing the latter file you will still need to select the correct 'Serial Port' for your device; but everything else should be good to go.

If you do make changes to the JS code, you can re-export a new SHSDS file and keep it somewhere safe in case you wish to restore the 'Custom Device' at a later point.

You're encouraged to contribute any enhancements back to this project if you come up with improved or additional effects. You can do this by creating a [Pull Request](https://github.com/GeorgeWilkins/Active-Belt-Tensioner/pulls).
