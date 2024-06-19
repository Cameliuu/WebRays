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

    // Create rendering animation
    var renderingAnimation = document.createElement('div');
    renderingAnimation.className = 'rendering-animation';
    document.body.appendChild(renderingAnimation);

    var renderingText = "rendering";
    var index = 0;

    function updateRenderingText() {
        var newText = "";
        for (var i = 0; i < renderingText.length; i++) {
            if (i === index) {
                newText += renderingText.charAt(i).toUpperCase();
            } else {
                newText += renderingText.charAt(i);
            }
        }
        renderingAnimation.textContent = newText;
        index = (index + 1) % renderingText.length;
    }

    var renderingInterval = setInterval(updateRenderingText, 200);

    var checkInitialization = setInterval(function() {
        if (Module.getAppInstace() !== null) {
            clearInterval(checkInitialization);
            // Initialization is complete, proceed with your code here
            console.log("App is initialized.");
            console.log(Module.getStartRender());
            createSphereDiv(Module.getObjs().get(0));
            clearInterval(renderingInterval); // Stop the rendering animation
            renderingAnimation.textContent = "Rendering complete"; // Update the text when rendering is complete
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
        console.log(Module.getConfig());
    }
    document.body.appendChild(button);
    document.body.appendChild(button2);

    // Create button to open the form for a new sphere
    var newSphereButton = document.createElement("button");
    newSphereButton.textContent = "Add New Sphere";
    newSphereButton.onclick = function () {
        openNewSphereForm();
    };
    document.body.appendChild(newSphereButton);

    // Create button to open the configuration form
    var configButton = document.createElement("button");
    configButton.textContent = "Change App Configuration";
    configButton.onclick = function () {
        openConfigForm();
    };
    document.body.appendChild(configButton);
};

function openConfigForm() {
    // Create the overlay
    const overlay = document.createElement("div");
    overlay.className = "config-overlay";

    // Create the form container
    const form = document.createElement("div");
    form.className = "config-form";

    // Function to create form inputs
    const createFormInput = (labelText, inputType = "text", value) => {
        const label = document.createElement("label");
        label.textContent = labelText;
        const input = document.createElement("input");
        input.type = inputType;
        input.value = value;
        form.appendChild(label);
        form.appendChild(input);
        return input;
    };
    var actualConfig = Module.getConfig();
    // Create form inputs
    const widthInput = createFormInput("Width:", "number",actualConfig.width);
    const heightInput = createFormInput("Height:", "number",actualConfig.height);
    const bgColorInput = createFormInput("Background Color:", "color",rgbToHex(actualConfig.color.getColorString()));
    const aaSamplesInput = createFormInput("Anti-Aliasing Samples:", "number",actualConfig.aaSamplings);

    // Create the submit button
    const submitButton = document.createElement("button");
    submitButton.textContent = "Apply Configuration";
    submitButton.onclick = function () {
        const width = parseInt(widthInput.value);
        const height = parseInt(heightInput.value);
        const bgColor = Module.Color.fromColorString(hexToColor(bgColorInput.value));
        const aaSamples = parseInt(aaSamplesInput.value);

        console.log("Applying configuration:", width, height, bgColor, aaSamples);

        Module.updateConfig(new Module.Config(width,height,bgColor,aaSamples));
        // Apply the configuration settings (assuming Module has appropriate methods)


        document.body.removeChild(overlay); // Remove the overlay after applying configuration
    };
    form.appendChild(submitButton);

    // Append form to the overlay and overlay to the body
    overlay.appendChild(form);
    document.body.appendChild(overlay);
}

function openNewSphereForm() {
    // Create the form container
    const formContainer = document.createElement("div");
    formContainer.className = "form-container";

    // Create the form element
    const form = document.createElement("form");
    form.id = "new-sphere-form";

    // Function to create form inputs
    const createFormInput = (labelText, inputType = "text") => {
        const label = document.createElement("label");
        label.textContent = labelText;
        const input = document.createElement("input");
        input.type = inputType;
        form.appendChild(label);
        form.appendChild(input);
        return input;
    };

    // Function to create color picker inputs
    const createColorPicker = (labelText) => {
        const label = document.createElement("label");
        label.textContent = labelText;
        const input = document.createElement("input");
        input.type = "color";
        form.appendChild(label);
        form.appendChild(input);
        return input;
    };

    // Create form inputs
    const centerXInput = createFormInput("Center X:");
    const centerYInput = createFormInput("Center Y:");
    const centerZInput = createFormInput("Center Z:");
    const radiusInput = createFormInput("Radius:");
    const materialAmbientInput = createColorPicker("Material Ambient:");
    const materialDiffuseInput = createColorPicker("Material Diffuse:");
    const materialSpecularInput = createColorPicker("Material Specular:");
    const shininessInput = createFormInput("Shininess:");
    const ambientStrengthInput = createFormInput("Ambient Strength:");

    // Create the submit button
    const submitButton = document.createElement("button");
    submitButton.type = "button";
    submitButton.textContent = "Create Sphere";
    submitButton.onclick = function () {
        const newSphere = new Module.Sphere(
            new Module.Vector3(
                parseFloat(centerXInput.value),
                parseFloat(centerYInput.value),
                parseFloat(centerZInput.value)
            ),
            parseFloat(radiusInput.value),
            new Module.Material(
                Module.Color.fromColorString(hexToColor(materialAmbientInput.value)),
                Module.Color.fromColorString(hexToColor(materialDiffuseInput.value)),
                Module.Color.fromColorString(hexToColor(materialSpecularInput.value)),
                parseFloat(shininessInput.value),
                parseFloat(ambientStrengthInput.value)
            ),
            29
        );
        console.log("Creating new sphere", newSphere);
        Module.addSphere(newSphere);
        createSphereDiv(newSphere);
        document.body.removeChild(formContainer);
    };
    form.appendChild(submitButton);

    // Append form to the container and container to the body
    formContainer.appendChild(form);
    document.body.appendChild(formContainer);
}

function createSphereDiv(sphere) {
    console.log("creating sphere div");
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

    const createColorPicker = (labelText, inputValue) => {
        const label = document.createElement("label");
        label.textContent = labelText;

        const input = document.createElement("input");
        input.type = "color";
        input.value = rgbToHex(inputValue);

        sphereDiv.appendChild(label);
        sphereDiv.appendChild(input);

        return input;
    };

    const centerXInput = createLabelAndInput("Center X:", center.x, "text");
    const centerYInput = createLabelAndInput("Center Y:", center.y, "text");
    const centerZInput = createLabelAndInput("Center Z:", center.z, "text");
    const radiusInput = createLabelAndInput("Radius:", radius, "text");

    const materialAmbientInput = createColorPicker("Material Ambient:", material.ambient.getColorString());
    const materialDiffuseInput = createColorPicker("Material Diffuse:", material.diffuse.getColorString());
    const materialSpecularInput = createColorPicker("Material Specular:", material.specular.getColorString());

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
                Module.Color.fromColorString(hexToColor(materialAmbientInput.value)),
                Module.Color.fromColorString(hexToColor(materialDiffuseInput.value)),
                Module.Color.fromColorString(hexToColor(materialSpecularInput.value)),
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

// Helper function to convert hex color to Color object string
function hexToColor(hex) {
    const r = parseInt(hex.substring(1, 3), 16);
    const g = parseInt(hex.substring(3, 5), 16);
    const b = parseInt(hex.substring(5, 7), 16);
    return `RGBA(${r},${g},${b},255)`;
}

// Helper function to convert Color object string to hex color
function rgbToHex(colorString) {
    const values = colorString.match(/\d+/g);
    const r = parseInt(values[0]).toString(16).padStart(2, '0');
    const g = parseInt(values[1]).toString(16).padStart(2, '0');
    const b = parseInt(values[2]).toString(16).padStart(2, '0');
    return `#${r}${g}${b}`;
}
