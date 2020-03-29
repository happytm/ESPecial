const char MAIN_page[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width,initial-scale=1.0">
<html>
<!-- HTML_STYLE -->
<style>
    body {
        text-align: center;
        font-family: helvetica;
        background-color: lightskyblue;
    }

    form {
        display: flex;
    }

    .container {
        background-color: whitesmoke;
        display: flex;
        flex-direction: column;
        justify-content: center;
        border: solid 1px lightgray;
        border-radius: 5px;
        width: 400px;
        margin: auto;
    }

    .column {
        display: flex;
        flex-direction: column;
        width: 100%;
    }

    .row {
        display: flex;
        flex-direction: row;
        align-items: center;
        justify-content: space-between;
        flex-wrap: wrap;
    }

    #top-bar {
        display: flex;
        flex-direction: row;
        justify-content: flex-end;
        flex-wrap: wrap;
        border-bottom: solid 1px lightgray;
    }

    .row>.label {
        margin-left: 10px;
    }

    .set {
        display: flex;
        flex-direction: column;
        width: 100%;
        background-color: lightgray;
        padding: 10px;
    }

    .set>.set-inputs {
        display: flex;
        flex-direction: column;
    }

    .set>.set-inputs input {
        width: 80%;
        height: 30px;
        border: none;
        border-radius: 5px;
        padding-left: 10px;
        margin-top: 5px;
        margin-bottom: 5px;
    }

    select {
        width: 50%;
        height: 30px;
        border: none;
        margin-top: 5px;
        margin-bottom: 5px;
    }

    .set>.set-buttons {
        display: flex;
        flex-direction: row;
        justify-content: flex-end;
    }

    .btn-container {
        display: flex;
    }

    .btn {
        border-radius: 5px;
        padding: 15px 32px;
        text-align: center;
        transition-duration: 0.4s;
        margin: 10px 5px;
        cursor: pointer;
        text-decoration: none;
    }

    .edit {
        background-color: dodgerblue;
        border: solid 1px dodgerblue;
        color: white;
    }

    .edit:hover {
        color: dodgerblue;
    }

    .on,
    .save {
        background-color: yellowgreen;
        border: solid 1px yellowgreen;
        color: white;
    }

    .on:hover,
    .save:hover {
        color: yellowgreen;
    }

    .off,
    .delete {
        background-color: tomato;
        border: solid 1px tomato;
        color: white;
    }

    .off:hover, .delete:hover {
        color: tomato;
    }

    .cancel {
        background-color: lightgray;
        border: solid 1px lightgray;
        color: white;
    }

    .cancel:hover {
        color: lightgray;
    }

    .btn:hover {
        background-color: white;
    }

    .input-mode {
        pointer-events: none;
        background-color: white;
    }

    .input-mode.on {
        color: yellowgreen;
    }

    .input-mode.off {
        color: tomato;
    }

    @media only screen and (max-width: 600px) {
        .container {
            width: 100%;
        }
    }
</style>
<!-- HTML_STYLE_END -->
<!-- HTML_DOM -->

<body>
    <h1>Dashboard</h1>
    <h3>Control and set gpios from esp32 chip</h3>
    <div class='container'>
        <div id='top-bar'>
            <a href="/update" class='btn edit'>update</a>
            <a onclick='addGpio()' class='btn edit'>+</a>
        </div>
        <div id='gpios' class='column'>
        </div>
    </div>
</body>

</html>
<!-- HTML_DOM_END -->
<!-- HTML_SCRIPT -->
<script>
    var gpios = []
    var availableGpios = []

    const fetchGpios = async () => {
        try {
            const res = await fetch(window.location.href + 'gpios');
            gpios = await res.json()
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    }

    const fetchAvailableGpios = async () => {
        try {
            const res = await fetch(window.location.href + 'gpios/available');
            availableGpios = await res.json()
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    }

    const switchState = async (element) => {
        try {
            const isOn = element.classList.value.includes('on')
            await fetch(`${window.location.href}digital/${element.id.split('-')[1]}/${isOn ? 0 : 1}`);
            element.classList.remove(isOn ? 'on' : 'off')
            element.classList.add(isOn ? 'off' : 'on')
            element.innerText = (isOn ? 'off' : 'on')
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    }

    const openSetting = (element) => {
        closeSettings()
        const gpio = gpios.find(gpio => gpio.pin === +element.id.split('-')[1])
        const row = document.getElementById('row-' + gpio.pin)
        if (!row.classList.value.includes('open')) {
            row.appendChild(createEditElement(gpio))
            row.classList.add('open')
        }
    }

    const saveSetting = async (element) => {
        const gpioPin = element.id.split('-')[1]
        const isNew = gpioPin === 'new'
        let req = { settings: {} }
        const newPin = document.getElementById(`setPin-${gpioPin}`).value
        const newLabel = document.getElementById(`setInputLabel-${gpioPin}`).value
        const newMode = document.getElementById(`setMode-${gpioPin}`).value
        if (newPin && newPin != gpioPin) {
            req.settings.pin = +newPin
        }
        if (newLabel) {
            req.settings.label = newLabel
        }
        if (newMode) {
            req.settings.mode = newMode
        }
        if (!isNew) {
            req.pin = gpioPin
        }
        try {
            const resp = await fetch(`${window.location.href}gpio${isNew ? '/new' : ''}`, {
                method: 'POST',
                headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(req)
            });
            const newSetting = await resp.json()
            let column = document.getElementById('gpios')
            if (isNew) {
                gpios.push(newSetting.settings)
                column.insertBefore(createGpioElement(newSetting.settings), column.firstChild)
                closeTabBar()
            } else {
                gpios = gpios.map(oldGpio => {
                    if (oldGpio.pin == +gpioPin) {
                        return { 'pin': newSetting.pin, 'label': newSetting.label, 'mode': newSetting.mode, 'state': newSetting.state }
                    }
                    return oldGpio
                })
                let oldRow = document.getElementById('row-' + gpioPin)
                column.replaceChild(createGpioElement(newSetting), oldRow)
            }
        } catch (err) {
            console.error(err)
        }
    }

    const deleteGpio = async (element) => {
        const gpioPin = element.id.split('-')[1]
        try {
            await fetch(`${window.location.href}gpio/${gpioPin}/delete`);
            await fetchGpios()
            let row = document.getElementById('row-' + gpioPin)
            closeSettings()
            let column = document.getElementById('gpios')
            column.removeChild(row)
        } catch (err) {
            console.error(err)
        }
    }

    const closeSettings = () => {
        document.querySelectorAll('.open').forEach(row => {
            row.classList.remove('open')
            row.removeChild(row.lastChild)
        })
    }

    const addGpio = () => {
        closeSettings()
        const topBar = document.getElementById('top-bar')
        if (!topBar.classList.value.includes('open')) {
            topBar.appendChild(createEditElement())
            topBar.classList.add('open')
        }
    }

    const updateModeOptions = (pin) => {
        const selectPin = document.getElementById(`setPin-${pin || 'new'}`)
        const selectMode = document.getElementById(`setMode-${pin || 'new'}`)

        const availableGpioInfos = availableGpios.find(gpio => gpio.pin == selectPin.value)
        if (availableGpioInfos.inputOnly && selectMode.childElementCount === 3) {
            selectMode.removeChild(selectMode.lastChild)
        } else if (!availableGpioInfos.inputOnly && selectMode.childElementCount === 2) {
            let option = document.createElement('div')
            option.innerHTML = `<option value=2>OUTPUT</option>`
            selectMode.appendChild(option.firstChild)
        }
    }
    // Element creation

    const createGpioElement = (gpio) => {
        let child = document.createElement('div');
        child.innerHTML = `<div class='row' id='row-${gpio.pin}'>
            <div class='label'> ${gpio.label}</div>
            <div class='btn-container'>
                <a onclick='openSetting(this)' id='edit-${gpio.pin}' class='btn edit'>edit</a>
                <a onclick='switchState(this)' id='state-${gpio.pin}' class='btn ${gpio.state ? 'on' : 'off'} ${gpio.mode != 2 ? 'input-mode' : ''}'>${gpio.state ? 'on' : 'off'}</a>
            </div>
        </div>`
        return child.firstChild;
    }

    const createEditElement = (gpio) => {
        if (!gpio) {
            gpio = {
                pin: 'new',
                label: 'Label will be displayed on the lcd screen'
            }
        }
        let modeOptions = `<option ${gpio.mode == 1 ? 'selected' : ''} value=1>INPUT</option><option ${gpio.mode == 5 ? 'selected' : ''} value=5>INPUT_PULLUP</option>`
        const pinOptions = availableGpios.reduce((prev, availableGpio) => {
            if ((!gpios.find(_gpio => _gpio.pin == availableGpio.pin) && availableGpio.pin != gpio.pin) || availableGpio.pin == gpio.pin) {
                // Complete the mode select input while we are here...
                if (availableGpio.pin == gpio.pin && !availableGpio.inputOnly) {
                    modeOptions += `<option ${gpio.mode == 2 ? 'selected' : ''} value=2>OUTPUT</option>`
                }
                prev += `<option ${availableGpio.pin == gpio.pin ? 'selected' : ''} value=${availableGpio.pin}>${availableGpio.pin}</option>`
            }
            return prev
        })
        let child = document.createElement('div')
        child.classList.add('set')
        child.innerHTML = `<div class='set-inputs'>
                <div class='row'>
                    <label for='pin'>pin:</label>
                    <select id='setPin-${gpio.pin}' name='pin' onchange='updateModeOptions(${gpio.pin})'>${pinOptions}</select>
                </div>
                <div class='row'>
                    <label for='label'>label:</label>
                    <input id='setInputLabel-${gpio.pin}' type='text' name='label' placeholder='${gpio.label}'>
                </div>
                <div class='row'>
                    <label for='mode'>input mode:</label>
                    <select id='setMode-${gpio.pin}' name='mode'>${modeOptions}</select>
                </div>
                </div>
            <div class='set-buttons'>
                <a onclick='closeSettings()' id='cancel-${gpio.pin}' class='btn cancel'>cancel</a>
                ${gpio.pin === "new" ? '' : `<a onclick='deleteGpio(this)' id='delete-${gpio.pin}' class='btn delete'>delete</a>`}
                <a onclick='saveSetting(this)' id='save-${gpio.pin}' class='btn save'>save</a>
            </div>`
        return child
    }

    window.onload = async () => {
        await fetchGpios()
        await fetchAvailableGpios()
        const container = document.getElementById('gpios')
        gpios.forEach(gpio => {
            container.appendChild(createGpioElement(gpio))
        })
    };
</script>
)=====";