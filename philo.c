/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:52:38 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/20 20:37:05 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
    t_program	program;
    t_philo		philosopher[PHILO_MAX];
    pthread_mutex_t	forks[PHILO_MAX];

    if (check_input(argc, argv) != 0)
        return (1);
    memset(&program, 0, sizeof(t_program));
    program.philos = malloc(sizeof(t_philo) * ft_atol(argv[1]));
    if (program.philos == NULL)
    {
        printf("Error: Failed to allocate memory for philosophers.\n");
        return (1);
    }
    if (!program.philos)
        return (1);
    init_mutexes(&program, philosopher);
    init_philos(&program, philosopher, forks);
    create_threads(philosopher);
    return (0);
}

int check_input(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        printf("Error: No arguments provided.\n");
        return (1);
    }
    if (check_arg(argc, argv) != 0)
        return (1);

    if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
    {
        printf("Error: Number of philosophers must be between 1 and 200.\n");
        return (1);
    }
    return (0);  // Eksik return değeri eklendi
}
/*
# Philosopher Projesi Roadmap

## 1. **Filozofların Rutinlerini Tamamlama**
   - **Düşünme (Thinking):**
     - Filozofun düşünme durumunu yazdır.
     - Çatal almadan önce düşünme süresi ekle.
   - **Çatal Alma (Taking Forks):**
     - Çift ve tek ID'li filozoflar için farklı çatal alma sırası belirle.
     - Mutex'leri kullanarak çatalları kilitle.
   - **Yemek Yeme (Eating):**
     - Yemek yeme süresini hesapla ve yazdır.
     - `last_meal` zamanını güncelle.
     - Yemek sayısını artır.
   - **Uyuma (Sleeping):**
     - Uyuma süresini hesapla ve yazdır.
     - Uyuma süresi boyunca bekle.
   - **Ölüm Kontrolü (Death Check):**
     - `dead_flag` kontrolü yaparak döngüyü sonlandır.

---

## 2. **Monitor Thread Eklemek**
   - **Ölüm Kontrolü:**
     - Her filozofun `last_meal` zamanını kontrol et.
     - Eğer bir filozofun `time_to_die` süresi dolmuşsa, ölüm durumunu yazdır ve programı sonlandır.
   - **Yemek Sayısı Kontrolü:**
     - Eğer tüm filozoflar belirli bir sayıda yemek yemişse, programı sonlandır.

---

## 3. **Deadlock Önleme**
   - **Çatal Alma Sırası:**
     - Çift ID'li filozoflar önce sağ çatalı, sonra sol çatalı almalı.
     - Tek ID'li filozoflar önce sol çatalı, sonra sağ çatalı almalı.
   - **Bekleme Süresi:**
     - Çatal alma sırasında küçük bir gecikme (`usleep`) ekle.
   - **Mutex Kullanımı:**
     - Çatallar için mutex'leri doğru sırada kilitle ve serbest bırak.

---

## 4. **Mutex ve Bellek Yönetimi**
   - **Mutex Destroy:**
     - Program sonunda tüm mutex'leri destroy et.
   - **Bellek Temizliği:**
     - `malloc` ile ayrılan bellekleri program sonunda serbest bırak.
   - **Hata Yönetimi:**
     - Mutex ve thread işlemlerinde hata kontrolü yap.
     - Hata durumunda kaynakları temizle ve programı sonlandır.

---

## 5. **Performans Optimizasyonu**
   - **Zaman Yönetimi:**
     - `get_time` fonksiyonunu optimize et.
     - `usleep` kullanımıyla CPU kullanımını azalt.
   - **Thread Senkronizasyonu:**
     - Gereksiz mutex kilitlemelerini kaldır.
     - Mutex kilitleme sırasını optimize et.

---

## 6. **Test ve Debug**
   - **Farklı Argüman Kombinasyonları:**
     - Farklı filozof sayıları ve zaman değerleriyle test yap.
   - **Deadlock Testi:**
     - Deadlock oluşup oluşmadığını kontrol et.
   - **Race Condition Testi:**
     - Aynı anda birden fazla thread'in aynı kaynağa erişip erişmediğini kontrol et.
   - **Bellek Sızıntısı Testi:**
     - `valgrind` veya benzeri araçlarla bellek sızıntılarını kontrol et.

---

## 7. **Dokümantasyon**
   - **README Dosyası:**
     - Projenin nasıl çalıştığını ve nasıl derleneceğini açıklayan bir README yaz.
   - **Kod Yorumları:**
     - Her fonksiyonun ne yaptığını açıklayan yorumlar ekle.
   - **Test Senaryoları:**
     - Kullanılan test senaryolarını dokümante et.

---

## 8. **Son Kontroller**
   - **Norminette Kontrolü:**
     - Kodunuzu 42 Norm kurallarına uygun hale getirin.
   - **Performans Testi:**
     - Büyük filozof sayılarıyla (örneğin 200) performansı test edin.
   - **Son Hata Kontrolleri:**
     - Tüm edge case'leri test edin ve hataları düzeltin.

Bu roadmap'i takip ederek projenizi adım adım tamamlayabilirsiniz.
*/