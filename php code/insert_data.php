<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "sensores";

// Criar conexão
$conn = new mysqli($servername, $username, $password, $dbname);

// Verificar conexão
if ($conn->connect_error) {
    die("Conexão falhou: " . $conn->connect_error);
}

// Receber dados do Arduino
$dados = file_get_contents("php://input");
$data = json_decode($dados, true);

// Adicionar depuração para verificar os dados recebidos
error_log("Dados recebidos: " . print_r($data, true), 3, "/xampp/htdocs/sensor_data/debug.log");

if ($data && isset($data['temperatura']) && isset($data['nivel']) && isset($data['pureza'])) {
    // Inserir dados na tabela correta
    $sql = "INSERT INTO caixa_dagua_collection (data_registro, temperatura, nivel, pureza) VALUES (NOW(), ?, ?, ?)";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("ddd", $data['temperatura'], $data['nivel'], $data['pureza']);
    $stmt->execute();

    echo "Novo registro criado com sucesso";
} else {
    echo "Erro: Dados inválidos";
}

// Fechar conexão
$conn->close();
?>

