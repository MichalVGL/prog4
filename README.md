# Use

- Build the project
- Set the startup project to Bomberman
- Run

# Used patterns
    -state pattern
        -Entity state
        -scene
    -observer
        -anything IObserver
        -GameObjectHandle (prevents lookups in a big objects vector)
    -subclass sandbox 
        -scene
        -controller
        -tilemod
        -...
    -flyweight
        -basetile/tilecomp
        -texturetoken/texture2D (and other entries/tokens)
    -servicelocator
        -2 seperate ones for the engine and bomberman
    -command
        -entity states
        -input handling
    -type object
        -levelscene/levelinfo and stageinfo
    -dirty flag
        -gameobject position
        -render order of gameobjects
        -text variable changes
    

    
    
# Engine design decisions
    -Resource system
        -entry for the path/id from sdbm_hash
        -token for identifying/interfacing with the resource in question. (and counting the amount of current usage)
        -texture/soundsystem are only used directly to set global settings (volume)

    -Camerasystem that has simple implementation to track targets and center itself

    -Extensive use of sdbm_hash for identification/quicker lookup
        -gameobjects
        -sound, textures, font
        -tilemod

    -Inputmanager is a singleton
    The only reason you need sdl and xinput in the bomberman project, ideally this would have been made into a system using the servicelocator and using an engine defined layer to abstract the input values from an engine definition to the xinput/sdl variant. 
    This would have taken too much time to implement so it remained as is.

    -GameObjectHandles as a wrapper for pointers to gameobjects.
    These handle will automatically be set to nullptr when the gameobject is deleted, making pointers to gameobjects safer and easier to do. Really usefull combined with the search functionality provided with the id's (sdbm_hash) of gameobjects.

    -ReqComp and OptComp. 
    Components often have to use other components to be used correctly.
    These wrappers around the pointers are used just for clarity of intend in your header and can be initialized with Init(). Given components cannot be deleted seperatly, reqcomp can be used without checking nullptr once it is initialized. (if the component is of the same parent, obviously)

    -SceneSystem uses a state pattern.
    Scenes have load/exit/update funtions, the update function return a pointer to a potentially new scene. This allows scenes to be defined seperatly from eachother and only having logic as to how it gets to the next scene. Resources are automatically cleaned up in between 2 scenes;

# Game design decision
    -Game is split up into tiles, it allows for better/less buggy implementations of spawning objects, movement and especially ai controllers.

    -Tilecomp contains just a basic tile (wall/ground) and optionally can contain a tilemod (usually a component inheriting form tilemod) that will change the behaviour of the tile. 1 tile can only have 1 tilemod.

    -Enemies and Players use the same entitycomp, the main difference between the 2 are the controllers given to the entitycomp. They use the exact same state system. There are some extension components (enemycomp,bombdeployercomp,...) to specify behaviour of the entity.


