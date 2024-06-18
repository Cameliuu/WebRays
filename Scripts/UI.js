function getInitializationStatus() {
    console.log(Module.getAppInstance === null);
}

function createSphereDiv(sphere) {
    console.log("creating sphere di");
    // Create a new div element
    const sphereDiv = document.createElement("div");
    sphereDiv.className = "sphere-properties";

    const titleDiv = document.createElement("div");
    titleDiv.className = "sphere-title";
    titleDiv.textContent = sphere.getTypeString() + " " + sphere.id;
    sphereDiv.appendChild(titleDiv);

    // Get properties from the sphere object
    const center = sphere.center;
    const radius = sphere.radius;
    const material = sphere.material;
    const id = sphere.id;
    console.log(sphere);

    // Create and append property elements
    const createLabelAndInput = (labelText, inputValue, inputType = "text") => {
        const label = document.createElement("label");
        label.textContent = labelText;

        const input = document.createElement("input");
        input.type = inputType;
        input.value = inputValue;


        sphereDiv.appendChild(label);
        sphereDiv.appendChild(input);

        return input;
    };

    const centerXInput = createLabelAndInput("Center X:", center.x, "text");
    const centerYInput = createLabelAndInput("Center Y:", center.y, "text");
    const centerZInput = createLabelAndInput("Center Z:", center.z, "text");
    const radiusInput = createLabelAndInput("Radius:", radius, "text");

    const materialAmbientInput = createLabelAndInput("Material Ambient:", material.ambient.getColorString());
    const materialDiffuseInput = createLabelAndInput("Material Diffuse:", material.diffuse.getColorString());
    const materialSpecularInput = createLabelAndInput("Material Specular:", material.specular.getColorString());

    const shininessInput = createLabelAndInput("Shininess:", material.shininess, "text");
    const ambientStrengthInput = createLabelAndInput("Ambient Strength:", material.ambientStrength, "text");

    // Append id as hidden input
    const idInput = document.createElement("input");
    idInput.type = "hidden";
    idInput.value = id;
    sphereDiv.appendChild(idInput);

    // Create a button to update the sphere
    const updateButton = document.createElement("button");
    updateButton.textContent = "Update Sphere";
    updateButton.onclick = function () {
        const updatedSphere = new Module.Sphere(
            new Module.Vector3(
                parseFloat(centerXInput.value),
                parseFloat(centerYInput.value),
                parseFloat(centerZInput.value)
            ),
            parseFloat(radiusInput.value),
            new Module.Material(
                Module.Color.fromColorString(materialAmbientInput.value),
                Module.Color.fromColorString(materialDiffuseInput.value),
                Module.Color.fromColorString(materialSpecularInput.value),
                parseFloat(shininessInput.value),
                parseFloat(ambientStrengthInput.value)
            ),
            parseInt(idInput.value)
        );
        console.log("Updating sphere", updatedSphere);
        Module.updateSphere(updatedSphere);
    };
    sphereDiv.appendChild(updateButton);

    // Append the new div to the sphere container
    document.getElementById('sphere-container').appendChild(sphereDiv);
}

Module.onRuntimeInitialized = () => {
    var sphereContainer = document.createElement('div');
    sphereContainer.className = "sphere-container";
    sphereContainer.id = "sphere-container";
    var input = document.createElement('input');
    // Set the type of the input element
    input.type = 'text';
    // Set an ID for the input element
    input.id = 'myTextInput';
    // Set a placeholder for the input element
    input.placeholder = 'Enter text here';
    document.body.appendChild(input);
    document.body.appendChild(sphereContainer);

    var checkInitialization = setInterval(function() {
        if (Module.getAppInstace() !== null) {
            clearInterval(checkInitialization);
            // Initialization is complete, proceed with your code here
            console.log("App is initialized.");
            console.log(Module.getStartRender());
            createSphereDiv(Module.getObjs().get(0));
        }
    }, 100);

    var color1 = new Module.Color(255,1,255,255);
    var color2 = new Module.Color(255,1,255,255);
    var color3 = new Module.Color(255,1,255,255);

    var vec = new Module.Vector3(0.1,0.2,0.3);
    var material = new Module.Material(color1,color2,color3,12,123);

    var sph = new Module.Sphere(vec,0.4,material,1);

    var button = document.createElement("button");
    var button2 = document.createElement("button");
    button2.id = "myButton"; // Changed id to remove '#'
    button2.textContent = "lala"; // Changed text to textContent
    button2.onclick = () =>{
        Module.switchRender();
    }
    button.textContent = "CLICK";

    button.onclick = () =>{
        console.log(Module.getStartRender());
        console.log(Module.getRenderingStarted());
    }
    document.body.appendChild(button);
    document.body.appendChild(button2);
}
