function stayHere()
{
    sessionStorage.setItem("modalConfirm", "true");
    document.getElementById("myModal").remove();
}



// Задаємо скоуп (scope) коду, чисто щоб не було проблем
(function () {

  // Ставимо рік у футері для копірайту
  let el = document.getElementById("year");
  if (el) el.textContent = new Date().getFullYear();

  // Якщо мова державна (або не дуже)
  let lang = navigator.language.toLowerCase();
  if(lang.includes("ua") || lang.includes("uk") || lang.includes("ru")){

    //Перевірка чи ми уже на укр версії
    if(window.location.href.includes("ua/")) return;

    let doFollow = sessionStorage.getItem("modalConfirm");

    // не діставати питаннями юзера знову і знову
    if(doFollow == "true") return;

    //створюємо модальне вікно олдскульним методом і маніпуляцією DOM
    let modal = document.createElement("div");
    modal.innerHTML = `
        <div style="background: gray; color: black; padding: 15px; border-radius:5px;">
            <div style="margin-bottom:10px;">Українська версія сайту доступна! Бажаєте перейти?</div>
            <a href="ua/">Перейти</a>
            <a href="javascript:stayHere()" style="float:right">Залишитися тут</a>
        </div>
    `;
    modal.style.position = "fixed";
    modal.style.top = "0";
    modal.style.bottom = "0";
    modal.style.left = "0";
    modal.style.right = "0";
    modal.style.backdropFilter = "blur(10px)";
    modal.style.display = "flex";
    modal.style.justifyContent = "center";
    modal.style.alignItems = "center";
    modal.id = "myModal";
    
    document.body.appendChild(modal);
  }

})();
