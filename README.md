# DirectShow Media Player :musical_note: :clapper:
Media Player Based On DirectX Show Application programming interface (API) Which is a media-streaming architecture for Microsoft Windows.

##Table of Contents :clipboard:
- [Software](https://github.com/Marloxo/DirectShow#software---space_invader)
- [Clone](https://github.com/Marloxo/DirectShow#clone-fork_and_knife)
- [Setup](https://github.com/Marloxo/DirectShow#setup-wrench)
- [FAQ](https://github.com/Marloxo/DirectShow#faq-speech_balloon)
- [License](https://github.com/Marloxo/DirectShow#license---pencil)


##Software   :space_invader:
Build on **Win32** project using **C++**. Make sure to have the newest version of *VS2015* installed before running the project.

The project folder is called **`DirectShow`**.

##Clone :fork_and_knife:
Clone this repo to your local machine using [`https://github.com/Marloxo/DirectShow.git`][1]

##Setup :wrench:
Just Make sure To have The latest DirectShow headers and libraries which available in the [Windows SDK.](http://go.microsoft.com/fwlink/p/?linkid=62332)

###Header Files
All DirectShow applications use the header file shown in the following table.

| Header File | Required For | 
| ----------- |:------------:|
| Dshow.h     | All DirectShow applications. |
 
Some DirectShow interfaces require additional header files. These requirements are noted in the interface reference.

###Library Files

DirectShow uses the static library files shown in the following table.

| Library File | Description | 
| ----------- |:------------:|
| Strmiids.lib | Exports class identifiers (CLSIDs) and interface identifiers (IIDs). |
| Quartz.lib | Exports the [AMGetErrorText][2] function. If you do not call this function, this library is not required. |

##FAQ :speech_balloon:
[Check out this link.][3]

##License   :pencil:
[![MIT Licence][4]][5]

This project is released into the public domain. For more information see  [LICENSE][6].


[1]: https://github.com/Marloxo/DirectShow/archive/master.zip
[2]: https://msdn.microsoft.com/en-us/library/windows/desktop/dd373430(v=vs.85).aspx
[3]: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375463(v=vs.85).aspx
[4]: https://img.shields.io/github/license/mashape/apistatus.svg?maxAge=2592000
[5]: https://opensource.org/licenses/mit-license.php
[6]: /LICENSE
