document.getElementById('chatForm').addEventListener('submit', function(e) {
    e.preventDefault(); // Prevents page reload

    const inputField = document.getElementById('userInput');
    const userText = inputField.value.trim();
    if (!userText) return;

    const chatWindow = document.getElementById('chatWindow');

    // 1. Hide welcome greeting on the first message
    const welcome = document.querySelector('.welcome-message');
    if (welcome) {
        welcome.remove();
    }

    // 2. Add the User's Message
    const userDiv = document.createElement('div');
    userDiv.className = 'message user-msg';
    userDiv.innerHTML = `
        <div class="avatar">A</div>
        <div>
            <strong>You</strong>
            <p>${userText}</p>
        </div>
    `;
    chatWindow.appendChild(userDiv);

    // Clear input box immediately
    inputField.value = '';

    // Scroll to bottom
    chatWindow.scrollTop = chatWindow.scrollHeight;

    // 3. Simulate AI response after a short delay
    setTimeout(() => {
        const aiDiv = document.createElement('div');
        aiDiv.className = 'message ai-msg';
        aiDiv.innerHTML = `
            <div class="avatar" style="background-color:#111;">✨</div>
            <div>
                <strong>My AI</strong>
                <p>This is a basic automated response simulating the chatbot view!</p>
            </div>
        `;
        chatWindow.appendChild(aiDiv);
        chatWindow.scrollTop = chatWindow.scrollHeight;
    }, 600);
});