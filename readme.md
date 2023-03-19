# Development setup steps:
1. Clone the repo
2. Download [compiled wxWidgets library](https://uowmailedu-my.sharepoint.com/:u:/g/personal/mb094_uowmail_edu_au/Een9ptEL2ipNtbqX1QoiNWABBfBJ4yKZlqmBqAE8bR4kQA?e=GmecLw), extract and copy the folder in the `resources` folder within the project.
3. Download [compiled Boost library](https://uowmailedu-my.sharepoint.com/:u:/g/personal/mb094_uowmail_edu_au/ERPsDLjejB5Et7IDClXvJ5MBD291cjTK03XjTatSFw4CgQ?e=FPoDjB), extract and copy the folder in the `resources` folder within the project.
4. Download [Oracle Database XE Bin](https://uowmailedu-my.sharepoint.com/:u:/g/personal/mb094_uowmail_edu_au/ERhZDelDG_ZAiRyNx8zbthMBulMbVEZXm9R6wnxW7psuow?e=FFxOaq), extract and copy the folder in the `resources` folder within the project.
5. Run the batch script `set path.bat`. The script is located under `support files` folder.

 # SideNotes:
- Projects' configurations are set on Debug & Release, 64-bit mode.
- All libraries used are `64-bit based`. The system should be 64-bit.  
- The environment variable `PATH` must have the cloned repo path, otherwise the program will not start (Run the script as admin if needed). 
- A release version of the program can be found under [Releases](https://github.com/Wakatem/RapidDB/releases)  

 # Tools & Libraries used:
- Visual Studio IDE 2022
- OCCI Instant Client
- Oracle Database XE
- wxWidgets
- Boost
- C++17
- PL/SQL