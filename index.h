const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<meta name="viewport" content="width=device-width,initial-scale=1.0">
<html>
<!-- HTML_STYLE -->
<style>
    body {
        text-align: center;
        font-family: helvetica;
        background-color: lightskyblue;
        margin: 0;
    }

    form {
        display: flex;
    }

    .spacer {
        display: block;
        width: 100%;
        height: 80px;
    }

    .header {
        display: flex;
        position: fixed;
        top: 0;
        width: 100%;
        background-color: white;
    }

    .container {
        background-color: whitesmoke;
        display: flex;
        flex-direction: column;
        justify-content: center;
        border: solid 1px lightgray;
        border-radius: 5px;
        width: 500px;
        margin: auto;
        margin-bottom: 10px;
    }

    .column {
        display: flex;
        flex-direction: column;
        width: 100%;
    }

    .setting-container {
        display: flex;
        flex-direction: column;
        border-bottom: 1px solid lightgray;
    }
    .setting-container form {
        flex-wrap: wrap;
        justify-content: flex-end;
        padding: 10px;
    }
    .setting-container label {
        display: flex;
        align-items: center;
        justify-content: flex-start;
        width: calc(35% - 10px);
        margin: 5px 0 5px;
        text-align: left;
    }
    .setting-container input[type='text'], input[type='checkbox'] {
        width: 65%;
        margin: 5px 0 5px;
        height: 30px;
        border: none;
        border-radius: 5px;
        padding-left: 9px;
    }
    #file-update-label {
        background-color: white;
        border-radius: 5px;
        padding: 5px;
        height: 30px;
        margin: auto;
        width: 70%;
    }
    .row {
        display: flex;
        flex-direction: row;
        align-items: center;
        justify-content: space-between;
        flex-wrap: wrap;
    }

    .hidden {
        display: none !important;
    }

    .header-container {
        display: flex;
        flex-direction: row;
        justify-content: space-between;
        flex-wrap: wrap;
        border-bottom: solid 1px lightgray;
    }

    .header-container > h2 {
        padding-left: 10px;
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
        width: 50%;
        height: 30px;
        border: none;
        border-radius: 5px;
        padding-left: 10px;
        margin-top: 5px;
        margin-bottom: 5px;
    }

    select {
        width: calc(50% + 10px);
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
    #condition-editor select,#condition-editor input, #condition-editor-result>.row select, #condition-editor-result>.row input{
        width: 15%;
    }
    #blocker {
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        top: 0;
        left: 0;
        z-index: 1;
        position: fixed;
        height: 100%;
        width: 100%;
        background: lightgray;
        opacity: 0.95;
        color: white;
    }
    #mqtt-retry-loader {
        height: 100%;
        width: 100%;
    }
    #mqtt-retry-loader div {
        border-width: 2px;
    }
    .spinner {
        height: 30px;
        border-radius: 5px;
        background-color: lightgray;
    }
    .lds-ring {
        width: 50px;
        height: 50px;
        display: inline-block;
        position: relative;
    }
    .lds-ring div {
        box-sizing: border-box;
        display: block;
        position: absolute;
        width: 100%;
        height: 100%;
        border: 8px solid #fff;
        border-radius: 50%;
        animation: lds-ring 1.2s cubic-bezier(0.5, 0, 0.5, 1) infinite;
        border-color: #fff transparent transparent transparent;
    }
    .lds-ring div:nth-child(1) {
        animation-delay: -0.45s;
    }
    .lds-ring div:nth-child(2) {
        animation-delay: -0.3s;
    }
    .lds-ring div:nth-child(3) {
        animation-delay: -0.15s;
    }
    @keyframes lds-ring {
        0% {
            transform: rotate(0deg);
        }
        100% {
            transform: rotate(360deg);
        }
    }
    @media only screen and (max-width: 600px) {
        body {
            margin: 0;
        }
        .container {
            width: 100%;
            border: none;
            border-radius: 0px;
        }
        .row {
            border-bottom: 1px solid lightgray
        }
    }
</style>
<!-- HTML_DOM -->
<body>
    <div class="spacer"></div>
    <div class="header">
        <a id='go-to-settings-button' onclick='switchPage()' class='btn edit'>settings</a>
        <a id='home-button' onclick='switchPage()' class='btn edit hidden'>Home</a>
    </div>
    <div class="lds-ring" id='page-loader'><div></div><div></div><div></div><div></div></div>
    <div class='container' id="gpio-container">
        <div id='gpio-header-bar' class="header-container">
            <h2>Gpios control</h2>
            <a id='add-gpio' onclick='addGpio()' class='btn edit'>+</a>
        </div>
        <div id='gpios' class='column'></div>
    </div>
    <div class="container" id="action-container">
        <div id='action-header-bar' class="header-container">
            <h2>Actions</h2>
            <a id='add-action' onclick='addAction()' class='btn edit'>+</a>
        </div>
        <div id='actions' class='column'></div>
    </div>
    <div class="container hidden" id="setting-container">
        <div class='column'>
            <div id='update' class='setting-container'>
                <p>Software update</p>
                <form onsubmit='submitUpdate(event)' enctype='multipart/form-data' id='upload-form'>
                    <label for='file' id='file-update-label'>Choose file</label>
                    <input type='file' name='update' id='file' onchange='fillUpdateInput(this)' style=display:none>
                    <input id='submit-update-file' type='submit' class='btn save' value='Update'>
                </form>
            </div>
            <div id='mqtt' class='setting-container'>
                <p>MQTT</p>
                <form onsubmit='submitMqtt(event)' id='mqtt-form'>
                    <label for='mqtt-active'>Active:</label>
                    <input type='checkbox' name='active' id='mqtt-active'>
                    <label for='mqtt-fn'>Friendly name:</label>
                    <input type='text' name='fn' id='mqtt-fn'>
                    <label for='mqtt-host'>Host:</label>
                    <input type='text' name='host' id='mqtt-host'>
                    <label for='mqtt-port'>Port:</label>
                    <input type='text' name='port' id='mqtt-port'>
                    <label for='mqtt-user'>User:</label>
                    <input type='text' name='user' id='mqtt-user'>
                    <label for='mqtt-password'>Password:</label>
                    <input type='text' name='password' id='mqtt-password'>
                    <label for='mqtt-topic'>Topic:</label>
                    <input type='text' name='topic' id='mqtt-topic'>
                    <a class='btn edit hidden' id='mqtt-retry' onclick='mqttConnect()'>
                        <span>Retry</span>
                        <div class="lds-ring hidden" id='mqtt-retry-loader'><div></div><div></div><div></div><div></div></div>
                    </a>
                    <input id='submit-mqtt-pref' type='submit'class='btn save' value='Save'>
                </form>
            </div>
            <div id='telegram' class='setting-container'>
                <p>Telegram</p>
                <form onsubmit='submitTelegram(event)' id='telegram-form'>
                    <label for='telegram-active'>Active:</label>
                    <input type='checkbox' name='active' id='telegram-active'>
                    <label for='telegram-token'>Token:</label>
                    <input type='text' name='token' id='telegram-token'>
                    <label for='telegram-users'>Authorised users: (empty if public)</label>
                    <input type='text' name='users' id='telegram-users' placeholder="telegram user ids, separeted by a comma.">
                    <input id='submit-telegram-pref' type='submit'class='btn save' value='Save'>
                </form>
            </div>
        </div>
    </div>
    <div id='blocker' class='hidden'>
        <h2 id='blocker-title'>Loading</h2>
        <div class="lds-ring"><div></div><div></div><div></div><div></div></div>
    </div>
</body>

</html>
<!-- HTML_SCRIPT -->
<script>
    var settings = {};
    var gpios = [];
    var availableGpios = [];
    var actions = [];
    var isSettingsMenuActivated = false;

    const delay = (ms => new Promise(resolve => setTimeout(resolve, ms)));

    // Update software

    const fillUpdateInput = (element) => {
        const fileName = element.value.split('\\\\');
        document.getElementById('file-update-label').innerHTML = fileName[fileName.length-1];
    };

    const submitUpdate = async (e) => {
        e.preventDefault();
        const blocker = document.getElementById('blocker');
        blocker.classList.remove('hidden');
        document.getElementById('blocker-title').innerText = 'Loading new software, please wait...';
        const form = document.getElementById('upload-form');
        const data = new FormData(form);
        try {
            const res = await fetch(window.location.href + 'install', {
                method: 'POST',
                headers: { contentType: false, processData:false },
                body: data
            });
            blocker.classList.add('hidden');
            location.reload();
        } catch (err) {
            blocker.classList.add('hidden');
            console.error(`Error: ${err}`);
        }
    };

    // Telegram

    const submitTelegram = async (e) => {
        e.preventDefault();
        const active = +document.getElementById(`telegram-active`).checked;
        const token = document.getElementById(`telegram-token`).value;
        const users = document.getElementById(`telegram-users`).value.split(',').map(id => +id);
        if (token != settings.telegram.token || active != settings.telegram.active || (JSON.stringify(users.sort()) !== JSON.stringify(settings.telegram.users.sort()))) {
            try {
                const res = await fetch(window.location.href + 'telegram', {
                    method: 'POST',
                    headers: { contentType: false, processData:false },
                    body: JSON.stringify({token, active, users})
                });
                settings.telegram = {active, token};
            } catch (err) {
                console.error(`Error: ${err}`);
            }
        }
    };

    // MQTT

    const submitMqtt = async (e) => {
        e.preventDefault();
        const active = document.getElementById(`mqtt-active`).checked;
        const fn = document.getElementById(`mqtt-fn`).value;
        const host = document.getElementById(`mqtt-host`).value;
        const port = document.getElementById(`mqtt-port`).value;
        const user = document.getElementById(`mqtt-user`).value;
        const password = document.getElementById(`mqtt-password`).value;
        const topic = document.getElementById(`mqtt-topic`).value;
        try {
            await fetch(window.location.href + 'mqtt', {
                method: 'POST',
                headers: { contentType: false, processData:false },
                body: JSON.stringify({active, fn, host, port, user, password, topic})
            });
            settings.mqtt = {active, fn, host, port, user, password, topic};
            await mqttConnect();

        } catch (err) {
            console.error(`Error: ${err}`);
        }
    };

    const mqttConnect = async () => {
        const loader = document.getElementById(`mqtt-retry-loader`);
        const retryButton = document.getElementById(`mqtt-retry`);
        const retryText = retryButton.firstElementChild;
        try {
            retryText.classList.add('hidden');
            loader.classList.remove('hidden');
            await fetch(window.location.href + 'mqtt/retry');
            let mqttState = 0;
            while (mqttState === 0) {
                const res = await fetch(window.location.href + 'health');
                mqttState = (await res.json()).mqtt;
                await delay(1000); //avoid spaming esp32
            }
            if (mqttState == 1) {
                retryButton.classList.add('hidden');
            } else {
                retryButton.classList.remove('hidden');
            }
        } catch(err) {
            console.error(`Error: ${err}`);
        }
        loader.classList.add('hidden');
        retryText.classList.remove('hidden');
    };

    // Gpios

    const fetchGpios = async () => {
        try {
            const res = await fetch(window.location.href + 'gpios');
            const newGpios = await res.json();
            if (newGpios && newGpios.length) {
                gpios = newGpios;
            }
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    };

    const fetchAvailableGpios = async () => {
        try {
            const res = await fetch(window.location.href + 'gpios/available');
            availableGpios = await res.json();
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    };

    const switchGpioState = async (element) => {
        try {
            const isOn = element.classList.value.includes('on');
            await fetch(`${window.location.href}digital/${element.id.split('-')[1]}/${isOn ? 0 : 1}`);
            element.classList.remove(isOn ? 'on' : 'off');
            element.classList.add(isOn ? 'off' : 'on');
            element.innerText = (isOn ? 'off' : 'on');
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    };

    const addGpio = () => {
        closeAnySettings();
        const topBar = document.getElementById('gpio-header-bar');
        if (!topBar.classList.value.includes('open')) {
            topBar.appendChild(createEditGpioPanel());
            topBar.classList.add('open');
        }
    };

    const deleteGpio = async (element) => {
        const gpioPin = element.id.split('-')[1];
        try {
            await fetch(`${window.location.href}gpio/${gpioPin}`, {method: 'DELETE'});
            await fetchGpios();
            let row = document.getElementById('rowGpio-' + gpioPin);
            closeAnySettings();
            let column = document.getElementById('gpios');
            column.removeChild(row);
        } catch (err) {
            console.error(err);
        }
    };

    // Actions
    const fetchActions = async () => {
        try {
            const res = await fetch(window.location.href + 'actions');
            const newActions = await res.json();
            if (newActions && newActions.length) {
                actions = newActions;
            }
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    };

    const runAction = async (element) => {
        const actionId = element.id.split('-')[1];
        try {
            await fetch(window.location.href + 'action/run/'+actionId);
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    };

    const addAction = () => {
        closeAnySettings();
        const topBar = document.getElementById('action-header-bar');
        if (!topBar.classList.value.includes('open')) {
            topBar.appendChild(createEditActionPanel());
            addConditionEditor(true);
            topBar.classList.add('open');
        }
    };

    const deleteAction = async (element) => {
        const actionId = element.id.split('-')[1];
        try {
            await fetch(`${window.location.href}action/${actionId}`, {method: 'DELETE'});
            await fetchActions();
            let row = document.getElementById('rowAction-' + actionId);
            closeAnySettings();
            let column = document.getElementById('actions');
            column.removeChild(row);
        } catch (err) {
            console.error(err);
        }
    };

    // Settings

    const fetchSettings = async () => {
        try {
            const res = await fetch(window.location.href + 'settings');
            const s = await res.json();
            if (s) {
                // Save settings
                settings = s;
                // Add them to the dom
                document.getElementById(`telegram-active`).checked = settings.telegram.active;
                document.getElementById(`telegram-token`).value = settings.telegram.token;
                document.getElementById(`telegram-users`).value = settings.telegram.users.filter(userId => userId != 0).join(',');
                document.getElementById(`mqtt-active`).checked = settings.mqtt.active;
                document.getElementById(`mqtt-fn`).value = settings.mqtt.fn;
                document.getElementById(`mqtt-host`).value = settings.mqtt.host;
                document.getElementById(`mqtt-port`).value = settings.mqtt.port;
                document.getElementById(`mqtt-user`).value = settings.mqtt.user;
                document.getElementById(`mqtt-password`).value = settings.mqtt.password;
                document.getElementById(`mqtt-topic`).value = settings.mqtt.topic;
            }
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    };

    const saveGpioSetting = async (element) => {
        const gpioPin = element.id.split('-')[1];
        const isNew = (gpioPin === 'new');
        let req = { settings: {} };
        const newPin = document.getElementById(`setGpioPin-${gpioPin}`).value;
        req.settings.label = newLabel = document.getElementById(`setGpioLabel-${gpioPin}`).value;
        req.settings.mode = newMode = document.getElementById(`setGpioMode-${gpioPin}`).value;
        req.settings.save = document.getElementById(`setGpioSave-${gpioPin}`).checked;
        if (newPin && newPin != gpioPin) {
            req.settings.pin = +newPin;
        }
        if (!isNew) {
            req.pin = gpioPin;
        }
        try {
            if (!newMode || !newLabel) {
                throw new Error('Parameters missing, please fill all the inputs');
            }
            const resp = await fetch(`${window.location.href}gpio`, {
                method: isNew ? 'POST' : 'PUT',
                headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(req)
            });
            const newSetting = await resp.json();
            let column = document.getElementById('gpios');
            if (isNew) {
                gpios.push(newSetting);
                column.insertBefore(createGpioControlRow(newSetting), column.firstChild);
                closeAnySettings();
            } else {
                gpios = gpios.map(oldGpio => (oldGpio.pin == +gpioPin) ? { ...newSetting } : oldGpio);
                let oldRow = document.getElementById('rowGpio-' + gpioPin);
                column.replaceChild(createGpioControlRow(newSetting), oldRow);
            }
        } catch (err) {
            console.error(err);
        }
    };

    const saveActionSetting = async (element) => {
        const actionId = element.id.split('-')[1];
        const isNew = (actionId === 'new');
        let req = { settings: {} };
        if (!isNew) {
            req.id = actionId;
        }
        req.settings.label = document.getElementById(`setActionLabel-${actionId}`).value;
        req.settings.type = +document.getElementById(`setActionType-${actionId}`).value;
        req.settings.conditions = [...document.getElementById(`condition-editor-result`).childNodes].map(rowElement => {
            const id = +rowElement.id.split('-')[1];
            return [
                +document.getElementById(`addGpioCondition-${id}`).value,
                +document.getElementById(`addSignCondition-${id}`).value,
                +document.getElementById(`addValueCondition-${id}`).value,
                +document.getElementById(`addNextSignCondition-${id}`).value,
            ];
        })
        req.settings.autoRun = document.getElementById(`setActionAutoRun-${actionId}`).checked;
        req.settings.message = document.getElementById(`setActionMessage-${actionId}`).value;
        req.settings.pinC = +document.getElementById(`setActionPinC-${actionId}`).value;
        req.settings.valueC = +document.getElementById(`setActionPinValueC-${actionId}`).value;
        req.settings.loopCount = +document.getElementById(`setActionLoopCount-${actionId}`).value;
        req.settings.delay = +document.getElementById(`setActionDelay-${actionId}`).value;
        req.settings.nextActionId = +document.getElementById(`setNextAction-${actionId}`).value;
        try {
            if (!req.settings.label || !req.settings.type) {
                throw new Error('Parameters missing, please fill at least label and type inputs.');
            }
            const resp = await fetch(`${window.location.href}action`, {
                method: isNew ? 'POST' : 'PUT',
                headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(req)
            });
            const newSetting = await resp.json();
            let column = document.getElementById('actions');
            if (isNew) {
                actions.push(newSetting);
                column.insertBefore(createActionRow(newSetting), column.firstChild);
                closeAnySettings();
            } else {
                actions = actions.map(oldAction => (oldAction.id == +actionId) ? {...newSetting} : oldAction);
                let oldRow = document.getElementById('rowAction-' + actionId);
                column.replaceChild(createActionRow(newSetting), oldRow);
            }
        } catch (err) {
            console.error(err);
        }
    };

    const openGpioSetting = (element) => {
        closeAnySettings();
        const gpio = gpios.find(gpio => gpio.pin === +element.id.split('-')[1]);
        const row = document.getElementById('rowGpio-' + gpio.pin);
        if (!row.classList.value.includes('open')) {
            row.appendChild(createEditGpioPanel(gpio));
            row.classList.add('open');
            document.getElementById(`setGpioSave-${gpio.pin}`).checked = gpio.save;
        }
    };

    const openActionSetting = (element) => {
        closeAnySettings();
        const action = actions.find(action => action.id === +element.id.split('-')[1]);
        const row = document.getElementById('rowAction-' + action.id);
        if (!row.classList.value.includes('open')) {
            row.appendChild(createEditActionPanel(action));
            addConditionEditor(true);
            // Fill conditions
            action.conditions.forEach(condition => {
                // Check if the condition contains a valid math operator sign
                if (condition[1]) {
                    addConditionEditor(false,condition);
                }
            })
            row.classList.add('open');
            document.getElementById(`setActionAutoRun-${action.id}`).checked = action.autoRun;
        }
    };

    const closeAnySettings = () => {
        document.querySelectorAll('.open').forEach(row => {
            row.classList.remove('open');
            row.removeChild(row.lastChild);
        });
    };

    // Element creation

    const switchPage = () => {
        isSettingsMenuActivated = !isSettingsMenuActivated;
        if (isSettingsMenuActivated) {
            document.getElementById('go-to-settings-button').classList.add('hidden');
            document.getElementById('gpio-container').classList.add('hidden');
            document.getElementById('action-container').classList.add('hidden');
            document.getElementById('home-button').classList.remove('hidden');
            document.getElementById('setting-container').classList.remove('hidden');
        } else {
            document.getElementById('go-to-settings-button').classList.remove('hidden');
            document.getElementById('gpio-container').classList.remove('hidden');
            document.getElementById('action-container').classList.remove('hidden');
            document.getElementById('home-button').classList.add('hidden');
            document.getElementById('setting-container').classList.add('hidden');
        }
    };

    const createGpioControlRow = (gpio) => {
        let child = document.createElement('div');
        child.innerHTML = `<div class='row' id='rowGpio-${gpio.pin}'>
            <div class='label'> ${gpio.label}</div>
            <div class='btn-container'>
                <a onclick='openGpioSetting(this)' id='editGpio-${gpio.pin}' class='btn edit'>edit</a>
                <a onclick='switchGpioState(this)' id='stateGpio-${gpio.pin}' class='btn ${gpio.state ? 'on' : 'off'} ${gpio.mode != 2 ? 'input-mode' : ''}'>${gpio.state ? 'on' : 'off'}</a>
            </div>
        </div>`;
        return child.firstChild;
    };

    const createActionRow = (action) => {
        let child = document.createElement('div');
        child.innerHTML = `<div class='row' id='rowAction-${action.id}'>
            <div class='label'> ${action.label}</div>
            <div class='btn-container'>
                <a onclick='openActionSetting(this)' id='editAction-${action.id}' class='btn edit'>edit</a>
                <a onclick='runAction(this)' id='runAction-${action.id}' class='btn on'>run</a>
            </div>
        </div>`;
        return child.firstChild;
    };

    // The edit panel for setting gpios
    const createEditGpioPanel = (gpio) => {
        if (!gpio) {
            gpio = {
                pin: 'new'
            };
        }
        let modeOptions = `<option ${gpio.mode == 1 ? 'selected' : ''} value=1>INPUT</option><option ${gpio.mode == 5 ? 'selected' : ''} value=5>INPUT_PULLUP</option>`;
        const pinOptions = availableGpios.reduce((prev, availableGpio) => {
            if ((!gpios.find(_gpio => _gpio.pin == availableGpio.pin) && availableGpio.pin != gpio.pin) || availableGpio.pin == gpio.pin) {
                // Complete the mode select input while we are here...
                if (availableGpio.pin == gpio.pin && !availableGpio.inputOnly) {
                    modeOptions += `<option ${gpio.mode == 2 ? 'selected' : ''} value=2>OUTPUT</option>`;
                }
                prev += `<option ${availableGpio.pin == gpio.pin ? 'selected' : ''} value=${availableGpio.pin}>${availableGpio.pin}</option>`;
            }
            return prev;
        },[]);
        let child = document.createElement('div');
        child.classList.add('set');
        child.innerHTML = `<div class='set-inputs'>
                <div class='row'>
                    <label for='setGpioPin-${gpio.pin}'>pin:</label>
                    <select id='setGpioPin-${gpio.pin}' name='pin' onchange='updateModeOptions("${gpio.pin}")'>${pinOptions}</select>
                </div>
                <div class='row'>
                    <label for='setGpioLabel-${gpio.pin}'>label:</label>
                    <input id='setGpioLabel-${gpio.pin}' type='text' name='label' value='${gpio.label || ''}' placeholder="Controller's title">
                </div>
                <div class='row'>
                    <label for='setGpioMode-${gpio.pin}'>input mode:</label>
                    <select id='setGpioMode-${gpio.pin}' name='mode'>${modeOptions}</select>
                </div>
                <div class='row'>
                    <label for='setGpioSave-${gpio.pin}'>Save state:</label>
                    <input type='checkbox' name='save' id='setGpioSave-${gpio.pin}' value='${gpio.save}'>
                </div>
                </div>
            <div class='set-buttons'>
                <a onclick='closeAnySettings()' id='cancelGpio-${gpio.pin}' class='btn cancel'>cancel</a>
                ${gpio.pin === "new" ? '' : `<a onclick='deleteGpio(this)' id='deleteGpio-${gpio.pin}' class='btn delete'>delete</a>`}
                <a onclick='saveGpioSetting(this)' id='saveGpio-${gpio.pin}' class='btn save'>save</a>
            </div>`;
        return child;
    };

    const deleteConditionEditor = (element) => {
        const rowNumber = +element.id.split('-')[1] || 0;
        const conditionEditorResultElement = document.getElementById(`condition-editor-result`);
        const conditionRowElement = document.getElementById(`condition-${rowNumber}`);
        conditionEditorResultElement.removeChild(conditionRowElement); 
    };

    const addConditionEditor = (editor, condition) => {
        let selectedGpio = 0;
        let selectedSign = 0;
        let selectedValue = 0;
        let selectedNextSign = 0;
        if (!editor && !condition) {
            selectedGpio = document.getElementById(`addGpioCondition`).value;
            selectedSign = document.getElementById(`addSignCondition`).value;
            selectedValue = document.getElementById(`addValueCondition`).value;
            selectedNextSign = document.getElementById(`addNextSignCondition`).value;
        } else if (condition) {
            selectedGpio = condition[0];
            selectedSign = condition[1];
            selectedValue = condition[2];
            selectedNextSign = condition[3];
        }

        let gpioConditionOptions = gpios.reduce((acc,gpio) =>  acc+`<option value=${gpio.pin} ${selectedGpio == gpio.pin ? 'selected':''}>${gpio.label}</option>`,``);
        
        const conditionEditorElement = editor && !condition ? document.getElementById(`condition-editor`) : document.getElementById(`condition-editor-result`);
        const conditionNumber = editor && !condition  ? '' : ('-' + conditionEditorElement.childElementCount);
        const rowElement = document.createElement('div');
        rowElement.id = editor && !condition ? 'condition-editor' : `condition${conditionNumber}`;
        rowElement.classList.add('row');
        rowElement.innerHTML = `<select id='addGpioCondition${conditionNumber}' name='gpioCondition'>${gpioConditionOptions}</select>
                        <select id='addSignCondition${conditionNumber}' name='signCondition'>
                            <option value=1 ${selectedSign == 1 ? 'selected':''}>=</option>
                            <option value=2 ${selectedSign == 2 ? 'selected':''}>!=</option>
                            <option value=3 ${selectedSign == 3 ? 'selected':''}>></option>
                            <option value=4 ${selectedSign == 4 ? 'selected':''}><</option>
                        </select>
                        <input type='number' id='addValueCondition${conditionNumber}' name='valueCondition' value='${selectedValue}' placeholder='value'>
                        <select id='addNextSignCondition${conditionNumber}' name='nextSignCondition'>
                            <option value=0 ${selectedNextSign == 0? 'selected':''}>none</option>
                            <option value=1 ${selectedNextSign == 1 ? 'selected':''}>AND</option>
                            <option value=2 ${selectedNextSign == 2 ? 'selected':''}>OR</option>
                            <option value=3 ${selectedNextSign == 3 ? 'selected':''}>NOR</option>
                        </select>
                        <a onclick='${editor && !condition ? `addConditionEditor()` : 'deleteConditionEditor(this)'}' id='${editor && !condition? 'addCondition': 'deleteCondition'}${conditionNumber}' class='btn ${editor && !condition ? 'save' : 'delete'}'>${editor && !condition ? 'add' : 'delete'}</a>`
        if (editor) {
            conditionEditorElement.replaceWith(rowElement);
        } else {
            conditionEditorElement.appendChild(rowElement);
        }
    };

    // The edit panel for setting gpios
    const createEditActionPanel = (action) => {
        if (!action) {
            action = {
                id: 'new',
                conditions: [],
                type: 1,
                loopCount: 0
            };
        }
        let nextActionOptions = actions.reduce((acc,a) => acc+`<option ${action.nextActionId === a.id ? 'selected' : ''} value=${a.id}>${a.label}</option>`,``);
        let gpioOptions = gpios.reduce((acc,gpio) =>  acc+`<option ${action.pinC === gpio.pin ? 'selected' : ''} value=${gpio.pin}>${gpio.label}</option>`,``);
        let gpioConditionOptions = gpios.reduce((acc,gpio) =>  acc+`<option value=${gpio.pin}>${gpio.label}</option>`,``);
        let child = document.createElement('div');
        child.classList.add('set');
        child.innerHTML = `<div class='set-inputs'>
                <div class='row'>
                    <label for='setActionLabel-${action.id}'>label:</label>
                    <input id='setActionLabel-${action.id}' type='text' name='label' value='${action.label||''}' placeholder='Describe your action'>
                </div>
                <div class='row'>
                    <label for='setActionAutoRun-${action.id}'>Auto run:</label>
                    <input type='checkbox' name='autorun' id='setActionAutoRun-${action.id}' value='${action.autoRun}'>
                </div>
                <div class='column'>
                    <div>Condition editor</div>
                    <div id='condition-editor' class='row'></div>
                    <div id='condition-editor-result' class="column"></div>
                </div>
                <div class='row'>
                    <label for='setActionType-${action.id}'>type:</label>
                    <select id='setActionType-${action.id}' name='type' onchange='updateActionTypes("${action.id}")'>
                        <option ${action.type === 1 ? 'selected' : ''} value=1>Send Telegram Notification</option>
                        <option ${action.type === 2 ? 'selected' : ''} value=2>Display on tft screen</option>
                        <option ${action.type === 3 ? 'selected' : ''} value=3>Set Pin to value</option>
                    </select>
                </div>
                <div class='row ${action.type === 3 ? 'hidden' : ''}'>
                    <label for='setActionMessage-${action.id}'>message:</label>
                    <input id='setActionMessage-${action.id}' type='text' name='message' value='${action.message||''}' placeholder='Message to display or send'>
                </div>
                <div class='row ${action.type !== 3 ? 'hidden' : ''}'>
                    <label for='setActionPinC-${action.id}'>Gpio to control:</label>
                    <select id='setActionPinC-${action.id}' name='gpio'>${gpioOptions}</select>
                </div>
                <div class='row ${action.type !== 3 ? 'hidden' : ''}'>
                    <label for='setActionPinValueC-${action.id}'>Gpio value:</label>
                    <input id='setActionPinValueC-${action.id}' type='number' name='gpioValue' value='${action.valueC||''}' placeholder='Set the gpio value when the action is triggered'>
                </div>
                <div class='row'>
                    <label for='setActionLoopCount-${action.id}'>Repeat action:</label>
                    <input id='setActionLoopCount-${action.id}' type='number' name='loopCount' value='${action.loopCount||''}' placeholder='How many times the action must be repeat'>
                </div>
                <div class='row'>
                    <label for='setActionDelay-${action.id}'>Delay between loop:</label>
                    <input id='setActionDelay-${action.id}' type='number' name='delay' value='${action.delay||''}' placeholder='Pause between each execution'>
                </div>
                <div class='row'>
                    <label for='setNextAction-${action.id}'>Next action:</label>
                    <select id='setNextAction-${action.id}' name='next'><option value=0>None</option>${nextActionOptions}</select>
                </div>
                </div>
            <div class='set-buttons'>
                <a onclick='closeAnySettings()' id='cancelAction-${action.id}' class='btn cancel'>cancel</a>
                ${action.id === "new" ? '' : `<a onclick='deleteAction(this)' id='deleteAction-${action.id}' class='btn delete'>delete</a>`}
                <a onclick='saveActionSetting(this)' id='saveAction-${action.id}' class='btn save'>save</a>
            </div>`;
        return child;
    };

    const createSpinner = () => {
        let spinner = document.createElement('div');
        spinner.classList.add('spinner');
        spinner.innerHTML = '<div class="lds-ring"><div></div><div></div><div></div><div></div></div>';
        return spinner;
    };

     // Change the input of available mode for a given pin
     const updateModeOptions = (pin) => {
        const selectPin = document.getElementById(`setGpioPin-${pin || 'new'}`);
        const selectMode = document.getElementById(`setGpioMode-${pin || 'new'}`);

        const availableGpioInfos = availableGpios.find(gpio => gpio.pin == selectPin.value);
        if (availableGpioInfos.inputOnly && selectMode.childElementCount === 3) {
            selectMode.removeChild(selectMode.lastChild);
        } else if (!availableGpioInfos.inputOnly && selectMode.childElementCount === 2) {
            let option = document.createElement('div');
            option.innerHTML = `<option value=2>OUTPUT</option>`;
            selectMode.appendChild(option.firstChild);
        }
    };

    const updateActionTypes = (id) => {
        const selectType = document.getElementById(`setActionType-${id || 'new'}`);
        if (+selectType.value !== 3) {
            document.getElementById(`setActionPinC-${id || 'new'}`).parentElement.classList.add('hidden');
            document.getElementById(`setActionPinValueC-${id || 'new'}`).parentElement.classList.add('hidden');
            document.getElementById(`setActionMessage-${id || 'new'}`).parentElement.classList.remove('hidden');
        } else {
            document.getElementById(`setActionPinC-${id || 'new'}`).parentElement.classList.remove('hidden');
            document.getElementById(`setActionPinValueC-${id || 'new'}`).parentElement.classList.remove('hidden');
            document.getElementById(`setActionMessage-${id || 'new'}`).parentElement.classList.add('hidden');
        }
    };

    // Events

    window.onload = async () => {
        await fetchGpios();
        const containerG = document.getElementById('gpios');
        gpios.forEach(gpio => {
            containerG.appendChild(createGpioControlRow(gpio));
        });
        await fetchActions();
        const containerA = document.getElementById('actions');
        actions.forEach(action => {
            containerA.appendChild(createActionRow(action));
        });
        await fetchSettings();
        document.getElementById('page-loader').remove();
        await fetchAvailableGpios();
    };
</script>
<!-- HTML_SCRIPT_END -->
)=====";