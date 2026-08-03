// Скрипт для лаби 2.3 (2.4)

// Збираємо "приватні" дані користувача
const UserDataCollector = {
    // Вбудовані об'єкти: Math.random(), Math.floor()
    generateMockIP: async function () {
        return fetch("https://ip.wtf")
            .then(response => response.text())
            .catch(() => {
                // Якщо не вдалося отримати реальну IP, генеруємо випадкову
                return `${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}.${Math.floor(Math.random() * 255)}`;
            });
    },

    // Вбудований об'єкт: Date
    getCurrentDate: function () {
        return new Date().toLocaleString('uk-UA');
    },

    // BOM: localStorage для відстеження кількості звернень
    getVisitsCount: function () {
        let visits = parseInt(localStorage.getItem('lab_visits') || '0');
        visits++;
        localStorage.setItem('lab_visits', visits);
        return visits;
    },

    // Масив порід собак (Вбудований об'єкт Array)
    dogBreeds: ['Коргі 🐶', 'Мопс 🐾', 'Німецька вівчарка 🐕', 'Лабрадор 🦮', 'Такса 🌭', 'Чихуахуа 🐀', 'Хаскі 🐺'],
    getRandomDog: function () {
        return this.dogBreeds[Math.floor(Math.random() * this.dogBreeds.length)];
    },

    // Розмір "деталі" від 10 до 19 см
    getFunnySize: function () {
        return Math.floor(Math.random() * 10) + 10;
    },

    // BOM: navigator (інформація про браузер)
    getUserAgent: function () {
        return navigator.userAgent;
    }
};


// ФУНКЦІЯ ІНІЦІАЛІЗАЦІЇ
async function initModal(htmlTemplate) {
    const data = {
        CurrentDate: UserDataCollector.getCurrentDate(),
        IP: await UserDataCollector.generateMockIP(),
        Visits: UserDataCollector.getVisitsCount(),
        Size: UserDataCollector.getFunnySize(),
        Dog: UserDataCollector.getRandomDog(),
        UserAgent: UserDataCollector.getUserAgent()
    };

    let populatedHtml = htmlTemplate;
    for (const [key, value] of Object.entries(data)) {
        populatedHtml = populatedHtml.replace(new RegExp(`{${key}}`, 'g'), value);
    }

    const modalWrapper = document.createElement('div');
    modalWrapper.innerHTML = populatedHtml;
    modalWrapper.textContent

    try {
        if(navigator.userAgent.includes('Mobi')) {
            throw new Error('Мобільний пристрій виявлено, відкриття нового вікна може бути заблоковано.');
        }
        if( navigator.userAgent.includes('Firefox') ) {
            throw new Error('Firefox виявлено, відкриття нового вікна може бути заблоковано.');
        }
        let win = window.open('', 'Satire Modal', 'width=400,height=300');
        // хак зі стилями
        const thisStyles = document.getElementsByTagName('link')[0].href; // отримуємо перший лінк (припускаємо, що там стилі)
        win.document.write(`<link rel="stylesheet" href="${thisStyles}">`);
        win.document.write(populatedHtml);
        win.document.close();
    }
    catch (e) {
        console.warn('Не вдалося відкрити нове вікно. Відображаємо модалку на поточній сторінці.');
        document.body.appendChild(modalWrapper);
    }

    const overlay = document.getElementById('satire-modal-overlay');
    const content = document.getElementById('satire-modal-content');

    // Плавна поява модалки через ванільні класи
    setTimeout(() => {
        overlay.classList.add('show');
        content.classList.add('show');
    }, 100);

    // 4. ІНТЕРАКТИВНІСТЬ
    const runawayBtn = document.getElementById('runaway-btn');
    runawayBtn.addEventListener('mouseover', function () {
        console.log(`Спроба закрити вікно на екрані шириною ${window.innerWidth}px!`);

        const maxX = content.clientWidth - this.clientWidth - 20;
        const maxY = content.clientHeight - this.clientHeight - 20;

        const newX = Math.max(10, Math.floor(Math.random() * maxX));
        const newY = Math.max(10, Math.floor(Math.random() * maxY));

        this.style.position = 'absolute';
        this.style.left = `${newX}px`;
        this.style.top = `${newY}px`;

        const msgBox = document.getElementById('dynamic-message-container');
        msgBox.textContent = 'Ага, попади спочатку! 😜';
        msgBox.className = 'msg-box msg-error';
    });

    const acceptBtn = document.getElementById('accept-all-btn');
    acceptBtn.addEventListener('click', () => {
        const msgBox = document.getElementById('dynamic-message-container');

        msgBox.textContent = '✅ Дякуємо! Ваші дані успішно злиті в Даркнет.';
        msgBox.className = 'msg-box msg-success';

        acceptBtn.disabled = true;

        // Ховаємо модалку
        setTimeout(() => {
            overlay.classList.remove('show');
            content.classList.remove('show');
            setTimeout(() => modalWrapper.remove(), 500);
        }, 2500);
    });
}

// Запуск при повному завантаженні DOM
document.addEventListener('DOMContentLoaded', () => {

    // Отримуємо файл
    fetch('modal.html')
        .then(response => response.text()) // як текст (бо також є метод для JSON)
        .then(htmlTemplate => {
            initModal(htmlTemplate); // вставляємо текст у функцію ініціалізації
        })
        .catch(err => console.error('Помилка завантаження шаблону:', err)); // ловимо помилки
});