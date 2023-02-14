# Setup Notes:
- Download [compiled wxWidgets library](https://uowmailedu-my.sharepoint.com/:u:/g/personal/mb094_uowmail_edu_au/Een9ptEL2ipNtbqX1QoiNWABBfBJ4yKZlqmBqAE8bR4kQA?e=GmecLw) and copy it in the `resources` folder within the project (if you are working on Gui).
- Projects' configurations are set on Debug, 64-bit mode.
- The OCCI library files are `64-bit based`. The system should be 64-bit.  
- If you are working on Logic project, unload Gui project, or vice versa (to avoid random build errors if things not setup properly).

# General Notes:  
- All configurations needed for integrating the OCCI library are done. Just clone the repo and test.
- Oracle Database on the system itself might be needed (not sure). Run the code and hopefully it works without asking for it (it shouldn't because we are using OCCI, a portable library).
- `Database`, a basic class for connecting to the database and running commands is implemented.

## Useful links to get started with OCCI API:  
- [Accessing Oracle Database Using C++](https://docs.oracle.com/database/121/LNCPP/relational.htm#LNCPP0031)
- [OCCI Classes and Methods](https://docs.oracle.com/database/121/LNCPP/reference001.htm#LNCPP20497)
- [Connection Class](https://docs.oracle.com/database/121/LNCPP/reference010.htm#LNCPP1007)
- [Environment Class](https://docs.oracle.com/database/121/LNCPP/reference014.htm#LNCPP1010)
- [Statement Class](https://docs.oracle.com/database/121/LNCPP/reference030.htm#LNCPP1022)
- [ResultSet Class](https://docs.oracle.com/database/121/LNCPP/reference027.htm#LNCPP1019)  