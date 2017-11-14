const localhost = window.location.origin.includes( 'localhost' );
if( !localhost ){
    if (location.protocol != 'https:'){
        location.href = 'https:' + window.location.href.substring( window.location.protocol.length );
    }
}

// logger
const log = document.getElementById( 'log' );
function println(){
    [ ...arguments ].forEach( arg => {
        log.innerHTML += arg + '<br>';
        log.scrollTop += 50;
    } );
}

// Blue web
const useBT = ! localhost;
let terminal = new BluetoothTerminal();

terminal.receive = data => {
    println( data + ' in' );
};

terminal._log = ( ...messages ) => {
    messages.forEach( message => {
        if( message ) println( message );
    } );
};

// UI / buttons events
document.querySelector( '#open-room' ).addEventListener( 'click', () => {
    const roomid = document.querySelector('#room-id').value;
    log.style.height = '50vh';

    if( useBT ){
        terminal.connect().then( () => {
            println( `connected to ${ terminal.getDeviceName() }` );
        } );
    }

    document.querySelector( '#pre-room' ).classList.toggle( 'hidden' );
    document.querySelector( '#in-room' ).classList.toggle( 'hidden' );
    document.querySelector( '#mainContainer' ).classList.toggle( 'bottom' );

    let cmd = '';
    document.querySelectorAll('.cmd-btn').forEach( d => {
        d.addEventListener( 'mousedown', e => {
            cmd = d.dataset.cmd;
            sendCmd();
        } );
        d.addEventListener( 'mouseup', e => {
            cmd = '';
        } );
    } );

    const socket = io();
    socket.on( 'cmd', data => {
        println( data );
        if( data.roomid === roomid ){
            if( useBT ){
                terminal.send( data.cmd ).then( () => println( data + ' out' ) ).catch( error => println( error ) );
            }
        }
    } );

    function sendCmd() {
        if ( cmd ) {
            if( useBT ){
                terminal.send( cmd ).then( () => println( cmd + ' out' ) ).catch( error => println( error ) );
            }
            else{
                socket.emit( 'cmd', { roomid, cmd } );
                println( `sending ${ cmd }` );
            }
            setTimeout( sendCmd, 400 );
        }
    }
} );

// utils
$(document).ready(function () {
    $('select').material_select();
});

function getSelectedText(elementId) {
    var elt = document.getElementById(elementId);

    if (elt.selectedIndex == -1)
        return null;

    return elt.options[elt.selectedIndex].text;
}
