## Drone Control & Specifications

The system supports three types of drones, each featuring a unique sensor suite and energy capacity.

### 1. General Commands and Energy Consumption
Several action performed by a drone consumes battery power. If the energy level reaches zero, the drone will become inactive and disconnect.

|   Command   |                                 Description                          |     Energy Cost   |
|-------------|----------------------------------------------------------------------|-------------------|
|     fwd     | Moves the drone 1 cell forward based on its current compass heading  |          5        |
|     +90     | Rotates the drone 90 degrees counter-clockwise                       |          4        |
|     -90     | Rotates the drone 90 degrees clockwise                               |          4        |
|     pov     | Activates active sensor to gather environmental data                 | Varies by sensor  |
|     map     | Shows full map of the simulation world                               |          0        |
|     exit    | Disconnects from the server and closes the connection                |          0        |


### 2. Sensor Types
Sensors allow the drone to detect obstacles and terrain features in the simulation. The cost is applied per activation (whenever the scan command is used).

|   Command   |     Sensor Type   |                   Coverage Area Description                  |     Energy Cost   |
|-------------|-------------------|--------------------------------------------------------------|-------------------|
|     s_a     |    Area Sensor    | Scans a square area surrounding the drone                    |          3        |
|     s_b     |    Strip Sensor   | Scans a straight line in the direction the drone is facing   |          1        |
|     s_c     |    Cone Sensor    | Scans a cone-shaped sector in front of the drone             |          2        |


### 3. Available Drone Models
When connecting to the server, you must choose one of the following models by typing its name:


#### Leleka

Energy Capacity: 300 units.
Hardware: Equipped with one Cone Sensor (s_c).
Role: An economical scout designed for precise, energy-efficient reconnaissance.

#### Shark

Energy Capacity: 500 units.
Hardware: Heavy-duty configuration. Carries a dual-sensor suite: Area Sensor (s_a) and Strip Sensor (s_b).
Role: High-awareness explorer. Best for mapping large areas quickly, though scanning consumes more power.

#### Octopus

Energy Capacity: 400 units.
Hardware: Equipped with one Cone Sensor (s_c).
Role: A balanced mid-range model with higher endurance than the Leleka.


### 4. World Grid & Environment
The environment is represented as a 2D grid of cells. Each cell contains a specific object or terrain type that affects drone movement and sensor readings.

Map Legend
When viewing the world or receiving scan data, the following symbols are used:

|    Symbol   |      Meaning     |                            Description                                  |
|-------------|------------------|-------------------------------------------------------------------------|
|      .      | Empty Space      | Clear airspace. Drones can move through these cell freely.              |
|      #      | Wall/Obstacle    | Solid terrain or a building. Drones cannot enter these cells.           |
|      E      | Exit Point       | The target destination or extraction zone.                              |
|      @      | Drone            | Represents your current position or the position of other active drones.|

### 5. Getting Started
1. Launch the Server: Ensure the C++ server is running and the world_grid.txt is present.
2. Connect the Client: Run the Python client script.
3. Choose a Model: Type the name (e.g., Shark) when prompted.
4. Explore: Send movement and scan commands to navigate the environment.