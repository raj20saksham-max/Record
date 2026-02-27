// 1. Data Loading: Browser ki memory (LocalStorage) se data nikalna
// Agar pehle se koi data nahi hai, toh khali array ([]) use hoga
let students = JSON.parse(localStorage.getItem('studentData')) || [];

// Page load hote hi table aur stats update karein
window.onload = function() {
    updateUI();
};

// 2. Add Student: Naya data array mein daalna
function handleAdd() {
    const name = document.getElementById('nameInput').value.trim();
    const roll = document.getElementById('rollInput').value;
    const marks = document.getElementById('marksInput').value;

    // Validation: Check karein ki koi field khali toh nahi hai
    if (!name || !roll || !marks) {
        alert("Bhai, saari details (Name, Roll, Marks) bhariye!");
        return;
    }

    // Naya student object (C struct ki tarah)
    const newStudent = {
        name: name,
        roll: parseInt(roll),
        marks: parseFloat(marks)
    };

    // Array mein push karein
    students.push(newStudent);
    
    // PERMANENT SAVE: Browser memory mein save karein
    saveData();

    // UI refresh aur input saaf karein
    updateUI();
    clearInputs();
}

// 3. UI Update: Table aur Dashboard stats refresh karna
function updateUI() {
    const tbody = document.querySelector("#dataTable tbody");
    if (!tbody) return;
    
    tbody.innerHTML = ""; // Purana table data saaf karein
    
    students.forEach(s => {
        const passStatus = s.marks >= 40 ? "✅ Pass" : "❌ Fail";
        tbody.innerHTML += `
            <tr>
                <td>#${s.roll}</td>
                <td><strong>${s.name}</strong></td>
                <td>${s.marks}%</td>
                <td>${passStatus}</td>
            </tr>`;
    });

    // Total count aur Topper update karein
    document.getElementById('totalCount').innerText = students.length;
    findTopper();
}

// 4. Find Topper: Sabse zyada marks wala student dhundna
function findTopper() {
    if (students.length === 0) {
        document.getElementById('topperName').innerText = "N/A";
        return;
    }
    // Array ko scan karke max marks wala student nikalna
    let topper = students.reduce((max, s) => s.marks > max.marks ? s : max, students[0]);
    document.getElementById('topperName').innerText = `${topper.name} (${topper.marks}%)`;
}

// 5. Search Logic: Name ya Roll se dhundna
function handleSearch() {
    const query = document.getElementById('searchInput').value.toLowerCase();
    const resultsPanel = document.getElementById('searchResults');
    const searchTbody = document.querySelector("#searchTable tbody");

    if (query === "") {
        resultsPanel.style.display = "none";
        return;
    }

    const filtered = students.filter(s => 
        s.name.toLowerCase().includes(query) || s.roll.toString() === query
    );

    searchTbody.innerHTML = "";
    resultsPanel.style.display = "block";

    if (filtered.length > 0) {
        filtered.forEach(s => {
            searchTbody.innerHTML += `<tr><td>#${s.roll}</td><td>${s.name}</td><td>${s.marks}%</td><td>Found</td></tr>`;
        });
    } else {
        searchTbody.innerHTML = "<tr><td colspan='4'>Record Not Found.</td></tr>";
    }
}

// 6. Sort Records: Marks ya Roll ke hisaab se
function sortRecords(type) {
    if (type === 'marks') {
        students.sort((a, b) => b.marks - a.marks); // High to Low
    } else {
        students.sort((a, b) => a.roll - b.roll); // Low to High
    }
    saveData();
    updateUI();
}

// Storage helper: Data ko browser memory mein save karna
function saveData() {
    localStorage.setItem('studentData', JSON.stringify(students));
}

// Input box saaf karne ke liye
function clearInputs() {
    document.getElementById('nameInput').value = '';
    document.getElementById('rollInput').value = '';
    document.getElementById('marksInput').value = '';
}