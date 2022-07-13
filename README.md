# ProiectAMD

The project I had to do at AMD Summer Practice Iasi 2022

The task was the following:

The idea of the project is to design and implement a CRUD(create, read, update, delete)
application. The shop will contain AMD’s products which will be grouped by category, and you will
have the option to filter your results by different criteria: price tag, release date, etc. You will also
have the ability to manage products and orders, based on your role on the platform.

Project sections:

# 1. The products:
The products are divided in 3 categories:
* CPUs;
* APUs
* GPUs.

Any product should have a weight, a height, a TDP, nms, a memory and clock frequency
The CPU will have a number of cores and threads, a socket;
The GPU will have a maximum resolution and support for different version of technologies
(OpenGL, DirectX);
The APU basically merge a CPU and a GPU in only one product.

# 2. The users:

The users are grouped in 2 categories:
* Administrator;
* Client

The shop should present a contextual menu based on roles (administrator/client).
As administrator, you can add/remove new products for selling and you also have the
permission to convert a client to admin role.
A client is a person who can add/remove items from its cart.
Any user should have its own unique number id, an username, a password and a role type (1-
for client and 2- for administrator).

# 3. Authentication and contextual menu:

You should implement a simple system to log in and identify the user type. After successful
login, you should have the following menu:
* Add items;
* Delete items;
* Add admin.
