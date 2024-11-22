const express = require('express');
const app = express();
const port = 3000;

// Simulation de l'état de l'interrupteur (peut être relié à un microcontrôleur)
let switchState = false;

// Route pour contrôler l'interrupteur
app.get('/switch', (req, res) => {
    const state = req.query.state;

    // Vérifier si l'état est valide
    if (state === '1') {
        switchState = true;  // Allumer l'interrupteur
        res.send('Interrupteur Allumé');
    } else if (state === '0') {
        switchState = false;  // Éteindre l'interrupteur
        res.send('Interrupteur Éteint');
    } else {
        res.status(400).send('État invalide');
    }
});

// Démarrer le serveur
app.listen(port, () => {
    console.log(`Serveur en cours d'exécution sur http://localhost:${port}`);
});
