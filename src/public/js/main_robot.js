const localhost = window.location.origin.includes( 'localhost' );
if( !localhost ) {
    if ( location.protocol != 'https:' ) {
        location.href = 'https:' + window.location.href.substring( window.location.protocol.length );
    }
}

// logger
const log = document.getElementById( 'log' );
function println() {
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
    log.style.height = '50px';
    let roomid = document.querySelector( '#room-id' ).value;

    document.getElementById( 'robotName' ).innerHTML = 'Robot ' + getSelectedText( 'room-id' );

    localStorage.setItem( connection.socketMessageEvent, roomid );

    if( useBT ){
        terminal.connect().then( () => {
            println( `connected to ${ terminal.getDeviceName() }` );
        } );
    }

    connection.open( roomid, () => {
        document.querySelector( '#pre-room' ).classList.toggle( 'hidden' );
        document.querySelector( '#in-room' ).classList.toggle( 'hidden' );
        document.querySelector( '#mainContainer' ).classList.toggle( 'bottom' );
        println( `Join bot here: https://makerschat.herokuapp.com/#${ connection.sessionid }` );

        connection.getSocket( socket => {
            socket.on( 'cmd', data => {
                println( data );
                if( data.roomid === roomid ){
                    if( useBT && Date.now() - data.ts < 1000 ){
                        terminal.send( data.cmd ).then( () => println( data + ' out' ) ).catch( error => println( error ) );
                    }
                }
            } );
        } );
    } );
} );

// utils
$( document ).ready( () => $( 'select' ).material_select() );

function getSelectedText( elementId ) {
    let elt = document.getElementById( elementId );

    if ( elt.selectedIndex == -1 )
        return null;

    return elt.options[ elt.selectedIndex ].text;
}
