
<html>
    <body>
<?php
    if (isset($_GET["n"])) {
        $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
        if ($socket === false) {
            echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
        }
        /*
        // ... (socket_create code)
        $address = '127.0.0.1'; // Listen on localhost
        $port = 12346; // Choose an available port
        if (socket_bind($socket, $address, $port) === false) {
            echo "socket_bind() failed: reason: " . socket_strerror(socket_last_error($socket)) . "\n";
        }
        // ... (socket_create and socket_bind code)
        if (socket_listen($socket, 5) === false) { // 5 pending connections
            echo "socket_listen() failed: reason: " . socket_strerror(socket_last_error($socket)) . "\n";
        }
        // ... (socket_create, socket_bind, and socket_listen code)
        echo "Waiting for connections...\n";
        $clientSocket = socket_accept($socket);
        if ($clientSocket === false) {
            echo "socket_accept() failed: reason: " . socket_strerror(socket_last_error($socket)) . "\n";
        } else {
            echo "Client connected!\n";
            // Now you can read from and write to $clientSocket
        }
        // ... (code to accept clientSocket)
        */
        socket_connect($socket, "127.0.0.1", 12345);
        //$input = socket_read($clientSocket, 1024); // Read up to 1024 bytes
        //echo "Received from client: " . $input . "\n";
        $n = $_GET["n"];
        $response = (string)$n;
        /*socket_write($clientSocket, $response, strlen($response));
        $n = 0;
        socket_close($clientSocket);
        socket_close($socket);*/
        socket_write($socket, $response, strlen($response));
        if ($n != 4) echo socket_read($socket, 1000, PHP_NORMAL_READ) . "\n";
        socket_close($socket);
    }
?>
        <form action = "index.php" method = "get">
            <label id = "n">Nhập n:</label>
            <input type = "text" id = "n" name = "n">
            <input type = "submit" value = "Tính">
        </form>
    </body>
</html>
