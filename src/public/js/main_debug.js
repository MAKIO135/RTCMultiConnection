const useBT = ! window.location.origin.includes( 'localhost' );

const log = document.createElement( 'p' );
log.style.width = '100vw';
log.style.height = '50px';
log.style.overflowY = 'scroll';
log.style.position = 'absolute';
log.style.top = '0';
log.style.left = '0';
log.style.background = 'black';
log.style.color = 'white';
log.style.fontFamily = 'monospace';
document.body.appendChild( log );

function println(){
    [ ...arguments ].forEach( arg => {
        log.innerHTML += arg + '<br>';
        log.scrollTop += 50;
    } );
}

$(document).ready(function () {
    $('select').material_select();
});

function getSelectedText(elementId) {
    var elt = document.getElementById(elementId);

    if (elt.selectedIndex == -1)
        return null;

    return elt.options[elt.selectedIndex].text;
}

// Blue web
let terminal = new BluetoothTerminal();

terminal.receive = data => {
    println( data, 'in' );
};

terminal._log = ( ...messages ) => {
    messages.forEach( message => {
        if( message ) println( message );
    } );
};

// UI / buttons events
document.querySelector( '#open-room' ).addEventListener( 'click', () => {
    let roomid = document.querySelector( '#room-id' ).value;

    document.getElementById('robotName').innerHTML = 'Robot ' + getSelectedText('room-id');

    localStorage.setItem( connection.socketMessageEvent, roomid );

    if( useBT ){
        terminal.connect().then( () => {
            println( `connected to ${ terminal.getDeviceName() }` );
        } );
    }

    connection.open( 'debug-' + roomid, () => {
        document.querySelector( '#pre-room' ).classList.toggle( 'hidden' );
        document.querySelector( '#in-room' ).classList.toggle( 'hidden' );
        document.querySelector('#mainContainer').classList.toggle('bottom');
        println( `Join bot here: https://makerschat.herokuapp.com/#${ connection.sessionid }` );

        connection.getSocket( socket => {
            socket.on( 'cmd', data => {
                println( data );
                if( data.roomid === roomid ){
                    if( useBT ){
                        terminal.send( data.cmd ).then( () => println( data, 'out' ) ).catch( error => println( error ) );
                    }
                }
            } );
        } );
    } );

    let cmd = '';
    document.querySelectorAll('.cmd-btn').forEach(d => {
        d.addEventListener('mousedown', e => {
            cmd = d.dataset.cmd;
            sendCmd();
        });
        d.addEventListener('mouseup', e => {
            cmd = '';
        });
    });

    function sendCmd() {
        if (cmd != '' ) {
            println( `sending ${ cmd }` );
            if( useBT ){
                terminal.send( cmd ).then( () => println( data, 'out' ) ).catch( error => println( error ) );
            }
            setTimeout( sendCmd, 400 );
        }
    }
} );
